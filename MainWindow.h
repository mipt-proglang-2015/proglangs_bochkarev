#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TableViewController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void onTableViewCellDidEndEditing(const QString& string);
    void onPythonInterpreterDidFail(const QString& msg);
    void onToolButtonPress(bool checked);
private:
    void subscribeToSignals() const;

    Ui::MainWindow *_ui;
    TableViewController *_tableViewController;
};

#endif // MAINWINDOW_H
