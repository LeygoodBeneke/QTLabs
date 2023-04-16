#include <QApplication>//включение определения класса приложения, из объекта которого, если требуется, можно запустить цикл событий
#include <QLabel> //подключаем класс виджета QLabel

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QLabel *label = new QLabel(QString::fromUtf8("Привет, Qt!")); //создание виджета текстовая метка QLabel, который выводит на экран сообщение “Привет, Qt!”
    label->show();//делаем текстовую метку видимой
    app.exec();
}
