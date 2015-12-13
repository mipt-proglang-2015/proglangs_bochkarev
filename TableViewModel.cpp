#include "TableViewModel.h"

#include <QFont>
#include <QBrush>
#include <sstream>
#include "common.h"

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
        return _gridData[row][col].value;
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
        QString result = value.toString();
        _gridData[index.row()][index.column()].rawValue = result;
        _gridData[index.row()][index.column()].value = result;
        processFormulaIfNeeded(result, index);
        Q_EMIT tableViewCellDidEndEditing( result );
    }
    return true;
}

Qt::ItemFlags TableViewModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void TableViewModel::processFormulaIfNeeded(const QString &value, const QModelIndex &index)
{
    if (value[0] == '=') {
        _gridData[index.row()][index.column()].isFormula = true;
        PythonValue result = PythonInterpreter::instance()->runSimpleString(value.mid(1, value.length() - 1));
        _gridData[index.row()][index.column()].value = result.stringValue;
    }
}
