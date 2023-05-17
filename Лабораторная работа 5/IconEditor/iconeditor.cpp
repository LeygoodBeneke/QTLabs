#include "iconeditor.h"
#include "ui_iconeditor.h"
#include <QPainter>
#include <QPaintEvent>

IconEditor::IconEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconEditor)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StaticContents);//?
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);//?

    curColor = Qt::black;//устанавливаем черный цвет пера
    zoom = 8;//коэффициент масштабирования устанавливается на 8, т.е. каждый пиксель иконки представляется квадратом 8*8


    image = QImage(16, 16, QImage::Format_ARGB32);//переменная для хранения иконок. инициализируем ее областью 16*16 пикселей и на 32-битовый формат ARGB, который поддерживает полупрозрачность
    image.fill(qRgba(0,0,0,0));//очищаем данные изображения, устанавливая признак прозрачности
}

IconEditor::~IconEditor()
{
    delete ui;
}

//функция возвращает идеальный размер виджета необходимый для менеджера компоновки
QSize IconEditor::sizeHint() const{
    QSize size = zoom*image.size();//размер изображения умножаем на масштабный коэффициент
    if (zoom >= 3){
        size += QSize(1,1);//добавляем еще один пиксель по каждому направлению для размещения сетки
    }
    return size;
}

//функция устанавливает текущий цвет чернил, который используется для закрашивания пикселей
void IconEditor::setPenColor(const QColor &newColor){
    curColor = newColor;
}

//подготавливает новое изображение к редактированию
void IconEditor::setIconImage(const QImage &newImage){
    if (newImage != image){
        image = newImage.convertToFormat(QImage::Format_ARGB32);//устанавливает глубину цвета равную 32 битам
        update();//принудительная перерисовка виджета с новым изображением
        updateGeometry();//сообщаем другим виджетам об изменении идеального размера виджета
    }
}

//устанавливаем масштабный коээфициент изображения
void IconEditor::setZoomFactor(int newZoom){
    if (newZoom < 1){
        newZoom = 1;//для предотвращения деления на 0 корректируем всякое значение, меньше 1
    }
    if (newZoom != zoom){
        zoom = newZoom;
        update();
        updateGeometry();
    }
}

void IconEditor::paintEvent(QPaintEvent *event){
    QPainter painter(this);//строим объект QPaint нашего виджета
    if (zoom >= 3){//если масштабный коэффициент равен или больше трех, то черчим с помощью функции drawLine сетку (при меньшем размере сетка не отображается)
        QPen pen(Qt::white, 0.1);
        painter.setPen(pen);//устанавливаем цвет линии, используя палитру виджета. используем ролевую функцию foreground() для получения кисти и извлечения из нее цвета

        for (int i = 0; i <= image.width(); ++i) painter.drawLine(zoom*i, 0, zoom*i, zoom *image.height());//чертим вертикальные линии
        for (int j = 0; j <= image.height(); ++j) painter.drawLine(0, zoom*j, zoom*image.width(), zoom*j);//чертим горизонтальные линии
    }
    for (int i = 0; i < image.width(); ++i){
        for (int j = 0; j <image.height(); ++j){
            QRect rect = pixelRect(i,j);//возвращает прямоугольник, определяющий область перерисовки
            if (event->region().intersects(rect)){
                QColor color = QColor::fromRgba(image.pixel(i, j));
                painter.fillRect(rect, color);//вывод на экран масштабируемого пикселя, передавая QColor в качестве кисти мы обеспечиваем равномерное заполнение области
            }
        }
    }
}

//функция возвращает объект прямоугольник для объекта QPainter
QRect IconEditor::pixelRect(int i, int j) const{//координаты пикселя в QImage (не в виджете)
    if (zoom >= 3){
        return QRect(zoom*i+1, zoom*j+1, zoom-1, zoom-1);//уменьшаем размеры прямоугольника на 1 пиксель, чтобы не загораживать линии сетки. входными параметрами здесь являются координаты верхнего левого угла прямоугольника  и размеры прямоугольника (ширина и высота)
    }else {
        return QRect(zoom*i,zoom*j, zoom, zoom);
    }
}

//событие нажатия кнопки мыши
void IconEditor::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        setImagePixel(event->pos(), true);//устанавливаем пиксель изображения
    }else if (event->button() == Qt::RightButton){
        setImagePixel(event->pos(), false);//стираем пиксель изображения
    }
}

//обрабатывает событие перемещения мышки при нажатой кнопки мышки
void IconEditor::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton){
        setImagePixel(event->pos(), true);
    }else if(event->buttons() & Qt::RightButton ){
        setImagePixel(event->pos(), false);
    }
}

//функция для установки или стирания пикселя. параметр pos определяет положение мышки на виджете
void IconEditor::setImagePixel(const QPoint &pos, bool opaque){
    //преобразуем полоожение из системы координат виджета в систему координат изображения
    int i = pos.x()/zoom;
    int j = pos.y()/zoom;
    //проверяем попадание точки в нужную область
    if (image.rect().contains(i,j)){
        if (opaque){
            image.setPixel(i,j,penColor().rgba());//устанавливаем пиксель в изображении, преобразуя перо в 32-битовое значение ARGB
        }else{
            image.setPixel(i,j,qRgba(0,0,0,0));//стираем пиксель, делая его прозрачным
        }
        update(pixelRect(i,j));//задаем область перерисовки
    }
}
