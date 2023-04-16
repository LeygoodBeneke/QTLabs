#include "window.h"
#include <QtCore5Compat/QTextCodec>//Подключаем заголовочный файл класса для смены кодировки

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF8");//создаем кодек и указываем название используемой кодовой таблицы
    QTextCodec::setCodecForLocale(codec);//связываем кодек со всеми строками C++
    setWindowTitle(codec->fromUnicode("Привет, Qt"));//устанавливаем заголовок окна
    resize(600,400);//меняем размер окна
}

Window::~Window()
{

}


