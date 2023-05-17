#include "hexspinbox.h"

HexSpinBox::HexSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    setRange(0,255);//устанавливаем диапазон изменения чисел от 0 до 255, в отличие от QSpinBox (0..99)
    validator = new QRegularExpressionValidator(QRegularExpression("[0-9A-Fa-f]{1,2}"), this);//ограничиваем набор допустимых воодимых символов шестнадцатиричными цифрами.
}

HexSpinBox::~HexSpinBox()
{
}

//функция вызывается для проверки допустимости введенного текста
QValidator::State HexSpinBox::validate(QString &text, int &pos) const{
    return  validator->validate(text, pos);
}

//функция преобразует число в  строку. используется для обновления окошка редактора после нажатия пользователем кнопок "вверх" и "вниз"
QString HexSpinBox::textFromValue(int value){
    //функция number возвращает шестнадцатиричное представление числа с символами в нижнем регистре. функция upper переводит их в верхний регистр
    return QString::number(value, 16).toUpper();//второй аргумент для функции number - это основание системы счисления.
}

//обратное преобразование из строки в число. вызывается когда пользователь вводит число с клавиатуры.
int HexSpinBox::valueFromText(const QString &text) const{
    bool ok;
    return text.toInt(&ok, 16);
}
