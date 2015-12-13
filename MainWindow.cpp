#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    setupTableView();

//    _ui->toolButton
//    QObject::connect(_ui->toolButton, SIGNAL(triggered(QAction*), )
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::onTableViewCellDidEndEditing(const QString &string)
{
    _ui->statusBar->clearMessage();
    _ui->statusBar->showMessage(string);
}

void MainWindow::setupTableView()
{
    _tableViewModel = new TableViewModel(0);
    _ui->tableView->setModel(_tableViewModel);

    QObject::connect(_tableViewModel, SIGNAL(tableViewCellDidEndEditing(QString)), this, SLOT(onTableViewCellDidEndEditing(QString)));
}
