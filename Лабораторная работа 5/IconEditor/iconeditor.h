#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include <QWidget>
//подключаем необходимые классы
#include <QColor>
#include <QImage>

namespace Ui {
class IconEditor;
}

class IconEditor : public QWidget
{
    Q_OBJECT
    //используем макрос для объявления пользовательских свойств
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    explicit IconEditor(QWidget *parent = 0);
    virtual ~IconEditor();
    //описываем методы реализующие работу со свойствами
    void setPenColor(const QColor &newColor);
    QColor penColor() const {return curColor;}

    void setZoomFactor(int newZoom);
    int zoomFactor() const {return zoom;}
    void setIconImage(const QImage &newImage);
    QImage iconImage() const {return image;}
    QSize sizeHint() const;//переопредленная виртуальная функция

protected:
    //обявление переопределяемых виртуальных функций
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::IconEditor *ui;
    //объявляем свойства и методы класса
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

    QColor curColor;
    QImage image;
    int zoom;
};

#endif // ICONEDITOR_H
