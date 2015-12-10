#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _tableViewModel = new TableViewModel(0);
    _ui->tableView->setModel(_tableViewModel);

//    _ui->toolButton
//    QObject::connect(_ui->toolButton, SIGNAL(triggered(QAction*), )
    QObject::connect(_tableViewModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(onTableViewEdit(QString)));
    QObject::connect(_tableViewModel, SIGNAL(editCompleted(QString)), this, SLOT(onTableViewEdit(QString)));
}

MainWindow::~MainWindow()
{
    delete _ui;
}


void MainWindow::onTableViewEdit(const QString &string)
{
    if (string.length() == 0) {
        _ui->statusBar->clearMessage();
    } else {
        _ui->statusBar->showMessage(string);
    }
}
