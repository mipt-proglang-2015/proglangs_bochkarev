#ifndef TABLEVIEWMODEL_H
#define TABLEVIEWMODEL_H

#include <QAbstractTableModel>
#include "CellData.h"
#include "common.h"

const int RowsCount = 255;
const int ColsCount = 26;

class TableViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableViewModel();
    TableViewModel(QObject *parent);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role);
    Qt::ItemFlags flags(const QModelIndex & index) const;

private:
    void processFormulaIfNeeded(const QString& value, const QModelIndex& index);

    CellData _gridData[RowsCount][ColsCount];  // holds text entered into QTableView
Q_SIGNALS:
    void tableViewCellDidEndEditing(const QString &);
};

#endif // TABLEVIEWMODEL_H
