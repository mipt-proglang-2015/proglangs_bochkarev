#include <QApplication>
#include <QTableView>

#include "mainwindow.h"
#include "tableviewmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    TableViewModel tableViewModel(0);
    QTableView tableView;
    tableView.setModel(&tableViewModel);
    tableView.show();
    return a.exec();
}
