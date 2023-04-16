#include <QApplication>
#include <QPushButton>


int main(int argc, char *argv[]){
    QApplication app(argc,argv);
    QPushButton *button = new QPushButton("Quit");
    //добавляем код обеспечивающий реакцию программы на действия пользователя (нажатие кнопки)
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
    button->show();
    return app.exec();
}
