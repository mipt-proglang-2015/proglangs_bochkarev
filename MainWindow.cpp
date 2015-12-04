#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tableViewModel = new TableViewModel(0);
    ui->tableView->setModel(tableViewModel);

    QObject::connect(tableViewModel, SIGNAL(editCompleted(QString)), this, SLOT(onTableViewEdit(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onTableViewEdit(const QString &string)
{
    if (string.length() == 0) {
        ui->statusBar->clearMessage();
    } else {
        ui->statusBar->showMessage(string);
    }
}
