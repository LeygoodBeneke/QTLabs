#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

//#include <QWidget> Данный класс использоваться не будет
#include <qspinbox.h> //подключаем файл класса родителя
#include <QRegularExpressionValidator>

class HexSpinBox : public QSpinBox //изменяем класс родитель
{
    Q_OBJECT// так класс не определяет своих собственных сигналов и слотов, то он не нуждается в макроопределении Q_OBJECT

public:
    HexSpinBox(QWidget *parent=0);
    ~HexSpinBox();

protected:
    //перекрываем две виртуальные функции родительского класса
    QString textFromValue(int value);
    int valueFromText(const QString &text) const;

    QValidator::State validate(QString &text, int &pos) const;

private:
    QRegularExpressionValidator *validator;
};


#endif // HEXSPINBOX_H
