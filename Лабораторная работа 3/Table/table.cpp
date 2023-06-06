#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(){

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    findDialog = 0;

    setCurrentFile("");

    setWindowIcon(QIcon::fromTheme("x-office-spreadsheet"));
}

void MainWindow::createActions(){

    /* -------- File -------- */
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    newAction->setIcon(QIcon::fromTheme("document-new"));
    connect(newAction, SIGNAL(triggered()),
            this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    openAction->setIcon(QIcon::fromTheme("document-open"));
    connect(openAction, SIGNAL(triggered()),
            this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save file"));
    saveAction->setIcon(QIcon::fromTheme("document-save"));
    connect(saveAction, SIGNAL(triggered()),
            this, SLOT(save()));

    saveAsAction = new QAction(tr("Save as..."), this);
    saveAsAction->setStatusTip(tr("Save file with a different name"));
    saveAsAction->setIcon(QIcon::fromTheme("document-save-as"));
    connect(saveAsAction, SIGNAL(triggered()),
            this, SLOT(saveAs()));

    for(int i = 0; i < MaxRecentFiles; i++){

        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setIcon(QIcon::fromTheme("window-close"));
    connect(exitAction, SIGNAL(triggered()),
            this, SLOT(close()));

    /* -------- Edit -------- */
    cutAction = new QAction(tr("Cut"), this);
    cutAction->setIcon(QIcon::fromTheme("edit-cut"));


    findAction = new QAction(tr("Find..."), this);
    findAction->setIcon(QIcon::fromTheme("edit-find"));
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

    goToCellAction = new QAction(tr("Go To Cell..."), this);
    goToCellAction->setIcon(QIcon::fromTheme("go-jump"));
    connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));



    sortAction = new QAction(tr("Sort..."), this);
    connect(sortAction, SIGNAL(triggered()),
            this, SLOT(sort()));

    /* -------- Options -------- */
    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);

    /* -------- Help -------- */
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setIcon(QIcon::fromTheme("help-about"));
    connect(aboutQtAction, SIGNAL(triggered()),
            qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus(){

    /* -------- File -------- */
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    separatorAction = fileMenu->addSeparator();

    for(int i = 0; i < MaxRecentFiles; i++)
        fileMenu->addAction(recentFileActions[i]);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    /* -------- Edit -------- */
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    /* -------- Tools -------- */
    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    /* -------- Options -------- */
    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalculateAction);

    /* -------- Help -------- */
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu(){

}

void MainWindow::createToolBars(){

    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->setMovable(false);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
    editToolBar->setMovable(false);
}

void MainWindow::createStatusBar(){

    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);


    updateStatusBar();
}

void MainWindow::updateStatusBar(){

}

void MainWindow::spreadsheetModified(){

    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::newFile(){
}

bool MainWindow::okToContinue(){

    if(isWindowModified()){
        int r = QMessageBox::warning(this, tr("Spreadsheet"), tr("The document has been modified. \nDo you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::Default,
                                     QMessageBox::No,
                                     QMessageBox::Cancel | QMessageBox::Escape);
        if(r == QMessageBox::Yes)
            return save();
        else if (r == QMessageBox::Cancel)
            return false;
    }

    return true;
}

void MainWindow::open(){

    if(okToContinue()){

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Spreadsheet"), ".", tr("Spreadsheet Files (*.sp)"));

        if(!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::loadFile(const QString &fileName){


    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::save(){

    if(curFile.isEmpty())
        return saveAs();
    else
        return saveFile(curFile);
}

bool MainWindow::saveFile(const QString &fileName){


    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File Saved"), 2000);
    return true;
}

bool MainWindow::saveAs(){

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));

    if(fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event){

    if(okToContinue()){
        writeSettings();
        event->accept();
    }else{
        event->ignore();
    }
}

void MainWindow::setCurrentFile(const QString &fileName){

    curFile = fileName;
    setWindowModified(false);

    QString shownName = "Untitled";

    if(!curFile.isEmpty()){
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString &fullFileName){

    return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateRecentFileActions(){

    QMutableStringListIterator i(recentFiles);

    while(i.hasNext()){

        if(!QFile::exists(i.next()))
            i.remove();
    }

    for(int j = 0; j < MaxRecentFiles; j++){

        if(j < recentFiles.count()){
            QString text = tr("&%1 %2").arg(j + 1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }else{
            recentFileActions[j]->setVisible(false);
        }
    }

    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile(){

    if(okToContinue()){

        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
            loadFile(action->data().toString());
    }
}

void MainWindow::find(){


}

void MainWindow::goToCell(){
}

void MainWindow::about(){

    QMessageBox::about(this, tr("About Spreadsheet"),
                       tr("<h2>Spreadsheet 1.0</h2>"));
}

void MainWindow::writeSettings(){

    QSettings settings("Software Inc.", "Spreadsheet");

    settings.setValue("geometry", geometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showGridAction->isChecked());
    settings.setValue("autoRecalc", autoRecalculateAction->isChecked());
}

void MainWindow::readSettings(){

    QSettings settings("Software Inc.", "Spreadsheet");

    QRect rect = settings.value("geometry", QRect(200, 200, 400, 400)).toRect();

    move(rect.topLeft());
    resize(rect.size());

    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid", true).toBool();
    showGridAction->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc", true).toBool();
    autoRecalculateAction->setChecked(autoRecalc);
}

void MainWindow::sort(){
}
