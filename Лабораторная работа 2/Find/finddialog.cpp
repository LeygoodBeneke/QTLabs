#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent) //передаем указатель на родительский виджет
{
    label = new QLabel(tr("Find &what:"));//& - применяется для управления фокусом посредством клавиши быстрого доступа Alt+W
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);//строка редактирования становится партнером текстовой метки label
    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search backward"));
    findButton = new QPushButton(tr("&Find"));//& - для задания клавиш быстрого доступа (Alt+F)
    findButton->setDefault(true);//кнопка Find будет использоваться по умолчанию, т.е. будет срабатывать при нажатии клавиши Enter
    findButton->setEnabled(false);//устанавливаем кнопку в неактивный режим. она становится недоступной для взаимодействия с пользователем. окрашивается в серый цвет.
    closeButton = new QPushButton(tr("Close"));
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));//слот вызывается при всяком изменении в строке редактирования
    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));//слот вызывается при нажатии пользователем кнопки Find
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));//диалоговое окно закрывается при нажатии кнопки Close
    QHBoxLayout *topLeftLayout = new QHBoxLayout;//менеджер горизонтальной компоновки
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);
    QVBoxLayout *leftLayout = new QVBoxLayout;//менеджер вертикальной компоновки
    leftLayout->addLayout(topLeftLayout);//менеджер topLeftLayout устанавливается как внутренний
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);
    QVBoxLayout *rightLayout = new QVBoxLayout;//менеджер вертикальной компоновки
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();
    QHBoxLayout *mainLayout = new QHBoxLayout;//менеджер горизонтальной компоновки
    mainLayout->addLayout(leftLayout);//менеджер leftLayout устанавливается как внутренний
    mainLayout->addLayout(rightLayout);//менеджер rightLayout устанавливается как внутренний
    setLayout(mainLayout);//установка главного менеджера компоновки. внешний менеджер ответственнен за всю область, занимаемую диалоговым окном.
    setWindowTitle(tr("Find"));//задаем название диалогового окна
    setFixedHeight(sizeHint().height());//утсанавливаем фиксированную высоту.
}

void FindDialog::findClicked(){
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive

                                                       :Qt::CaseInsensitive;
    if(backwardCheckBox->isChecked()){
        emit findPrevious(text, cs);//генерировать сигнал
    }else{
        emit findNext(text, cs);//генерировать сигнал
    }
}


void FindDialog::enableFindButton(const QString &text){
    findButton->setEnabled(!text.isEmpty());//установить активный режим кнопки в случае если в редактируемой строке есть текст
}
