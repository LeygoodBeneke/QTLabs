#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog> //включаем определение базового класса для диалоговых окон
//предварительное обявление классов

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog : public QDialog //наш класс наследуется от класса QDialog, родителем для которого является класс QWidget
{
    Q_OBJECT//макрос для MOC
public:
    explicit FindDialog(QWidget *parent = 0);//объявление конструктора, для которого невозможно неявное преобразование типов при инициализации. В конструкторе указывается родительский виджет. По умолчанию он равен 0, это значит что у данного виджета нет родителя

signals: //область объявления сигналов
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);
    void findNext(const QString &str, Qt::CaseSensitivity cs);
private slots://область объявления слотов
    void findClicked();// нажатие кнопки поиска
    void enableFindButton(const QString &text);//активация кнопки поиска



private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif // FINDDIALOG_H
