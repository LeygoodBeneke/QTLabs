#ifndef GOTOCELL_H
#define GOTOCELL_H
#include <QDialog>

namespace Ui {//определение нашего класса в пространстве имен Ui
    class Gotocell;
}

class Gotocell : public QDialog
{
    Q_OBJECT

public:
    explicit Gotocell(QWidget *parent = 0);
    ~Gotocell();

private:
    Ui::Gotocell *ui;//определение свойства необходимого для инициализации формы

private slots:
    void on_lineEdit_textChanged();
};

#endif // GOTOCELL_H
