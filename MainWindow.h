#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TableViewModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void onTableViewEdit(const QString& string);


private:
    Ui::MainWindow *ui;

    TableViewModel *tableViewModel;
};

#endif // MAINWINDOW_H
