#ifndef WINDOW_H //проверяет на однократное подключение данного файла
#define WINDOW_H

#include <QMainWindow> //подключаем класс меню

class Window : public QMainWindow //наш класс будет унаследован от класса меню
{
    Q_OBJECT // внедряет в файл необходимую объектную метаинформацию

public:
    Window(QWidget *parent = 0);//объявление конструктора. Параметр parent указывает на родительский виджет
    ~Window();//объявление деструктора
};

#endif // WINDOW_H

