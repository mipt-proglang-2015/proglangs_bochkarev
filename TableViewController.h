#ifndef STANDARTMODELWRAPPER_H
#define STANDARTMODELWRAPPER_H

#include <QObject>
#include <QStandardItemModel>
#include <QtWidgets/QTableView>
#include <QItemSelectionModel>

#include "CellData.h"

const int RowsCount = 255;
const int ColsCount = 26;

class TableViewController : public QObject
{
    Q_OBJECT
public:
    explicit TableViewController(QObject *parent = 0);
    explicit TableViewController(QTableView *tableView);

Q_SIGNALS:
    void tableViewCellDidEndEditing(const QString& value);
    void tableViewDidSelectCell(const QString& cellValue);
private Q_SLOTS:
    void onTableViewItemChanged(QStandardItem* item);
    void onTableViewDidSelectCell(const QItemSelection& selected, const QItemSelection& deselected);
private:
    QStandardItemModel* createStandartItemModel();

    QStandardItemModel* _model;
    QTableView* _tableView;
    CellData _gridData[RowsCount][ColsCount];

    bool _handleNextItemChange;
};

#endif // STANDARTMODELWRAPPER_H
