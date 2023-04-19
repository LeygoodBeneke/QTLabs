#include "gotocell.h"
#include "ui_gotocell.h"
#include <QValidator>


Gotocell::Gotocell(QWidget *parent) :
    QDialog(parent), ui(new Ui::Gotocell)//определение конструктора, передаем в качестве родителя класс QDialog, инициализируем свойство ui - как объект класса Ui::Gotocell
{
    ui->setupUi(this);//инициализация формы
    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}");//определение регулярного выражения - шаблона формата ячейки
    ui->lineEdit->setValidator(new QRegularExpressionValidator(regExp, this));//проверка правильности вводимых значений

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

Gotocell::~Gotocell()
{
    delete ui;//удаляем динамически созданный объект, для удаления его дочерних виджетов
}

void Gotocell::on_lineEdit_textChanged(){
    ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());//функция проверки допустимости значений заданных в конструкторе
}
