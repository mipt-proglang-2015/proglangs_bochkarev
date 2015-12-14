#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "InterpreterHandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _tableViewController = new TableViewController(_ui->tableView);
    subscribeToSignals();
}

MainWindow::~MainWindow()
{
    delete _ui;
    delete _tableViewController;
}

void MainWindow::subscribeToSignals() const
{
//    QObject::connect(_ui->toolButton, SIGNAL(clicked(bool)), this, SLOT(onToolButtonPress(bool)));
    QObject::connect(_tableViewController, SIGNAL(tableViewCellDidEndEditing(QString)), this, SLOT(onTableViewCellDidEndEditing(QString)));
    QObject::connect(_tableViewController, SIGNAL(tableViewDidSelectCell(QString)), this, SLOT(onTableViewCellDidEndEditing(QString)));
    QObject::connect(InterpreterHandler::instance(), SIGNAL(pythonInterpreterDidFail(QString)), this, SLOT(onPythonInterpreterDidFail(QString)));
}

// signal handlers
void MainWindow::onTableViewCellDidEndEditing(const QString &string)
{
    _ui->statusBar->clearMessage();
    _ui->statusBar->showMessage(string);
}

void MainWindow::onPythonInterpreterDidFail(const QString &msg)
{
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void MainWindow::onToolButtonPress(bool checked)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Python files (*)"));
    qDebug() << "File opened " + fileName;
}
