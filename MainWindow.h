#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TableViewModel.h"
#include "common.h"

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

private:
    void setupTableView();

    Ui::MainWindow *_ui;
    TableViewModel *_tableViewModel;
};

#endif // MAINWINDOW_H
