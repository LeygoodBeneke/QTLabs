#include "window.h"
#include <QApplication>//наследник класса QCoreApplication

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window w;//создаем объект нашего класса (элемент управления), невидимый по умолчанию
    w.show();//отображаем элемент управления

    return app.exec();
}
