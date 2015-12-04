#include "TableViewModel.h"

#include <QFont>
#include <QBrush>

TableViewModel::TableViewModel()
{}

TableViewModel::TableViewModel(QObject *parent) : QAbstractTableModel(parent)
{}

int TableViewModel::rowCount(const QModelIndex &) const
{
    return RowsCount;
}

int TableViewModel::columnCount(const QModelIndex &) const
{
    return ColsCount;
}

QVariant TableViewModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role) {
    case Qt::DisplayRole:
        return _gridData[row][col].rawValue;
        break;
    case Qt::FontRole:
        break;
    case Qt::TextAlignmentRole:
        break;
    default:
        break;
    }
    return QVariant();
}

bool TableViewModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole) {
        //save value from editor to member m_gridData
        _gridData[index.row()][index.column()].rawValue = value.toString();
        //for presentation purposes only: build and emit a joined string
        QString result;
        for(int row = 0; row < RowsCount; row++) {
            for(int col= 0; col < ColsCount; col++) {
                result += _gridData[row][col].rawValue + " ";
            }
        }

        emit editCompleted( result );
    }
    return true;
}

Qt::ItemFlags TableViewModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
