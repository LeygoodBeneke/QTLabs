#ifndef MAINWINDOW_H

#define MAINWINDOW_H



#include <QMainWindow>



class SpreadSheet;//являетс подклассом QTAbleWidget, обладающий возможностями электронной таблицы (поддерживает формулы)
class QAction;



namespace Ui {

class MainWindow;

}


class Table : public QMainWindow
{
    Q_OBJECT



public:

    explicit Table(QWidget *parent = 0);

    ~Table();



private:

    Ui::MainWindow *ui;

    SpreadSheet *spreadsheet;

    enum {maxRecentFile=5};

    QAction *recentFilesActions[maxRecentFile];

    QAction *addSeparator;



private slots:

    void newFile();

    void open();

    bool save();

    bool saveAs();

    void find();

    void goToCell();

    void about();

    void sort();

};



#endif // MAINWINDOW_H
