#include <QtGui>
#include "mainwindow.h"

#include "ui_mainwindow.h"

//#include "spreadsheet.h"



Table::Table(QWidget *parent) :

    QMainWindow(parent),

    ui(new Ui::MainWindow)

{

    ui->setupUi(this);

    //    spreadsheet = new SpreadSheet;

    //    setCentralWidget(spreadsheet);



    //connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}



Table::~Table()

{

    delete ui;

}



void Table::newFile(){}



void Table::open(){}



bool Table::save(){

    return true;

}



bool Table::saveAs(){

    return true;

}



void Table::find(){}



void Table::goToCell(){}



void Table::about(){}



void Table::sort(){}
