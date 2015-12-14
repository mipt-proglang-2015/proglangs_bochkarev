#include <QStringList>
#include <QDebug>

#include "TableViewController.h"
#include "InterpreterHandler.h"
#include "PythonInterpreter.h"

TableViewController::TableViewController(QObject *parent) :
    QObject(parent)
{
}

TableViewController::TableViewController(QTableView* tableView) : _tableView(tableView)
{
    _tableView->setModel(createStandartItemModel());

    // подписываемся на изменение текста ячейки
    QObject::connect(_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onTableViewItemChanged(QStandardItem*)));
    // подписываемся на подсвечивание ячейки
    QItemSelectionModel* sm = _tableView->selectionModel();
    QObject::connect(sm, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onTableViewDidSelectCell(QItemSelection,QItemSelection)));
}

QStandardItemModel* TableViewController::createStandartItemModel()
{
    _model = new QStandardItemModel(RowsCount, ColsCount);

    // init data
    for (int row = 0; row < RowsCount; ++row) {
        for (int col = 0; col < ColsCount; ++col) {
            QStandardItem *item = new QStandardItem(QString(""));
            _model->setItem(row, col, item);
        }
    }

    QStringList headersList = QStringList();
    for (int col = 0; col < ColsCount; ++col) {
        headersList << QString('A' + col);
    }
    _model->setHorizontalHeaderLabels(headersList);
    return _model;
}


// SLOTS
void TableViewController::onTableViewDidSelectCell(const QItemSelection& selected, const QItemSelection& deselected)
{
    QModelIndex selectedIndex = selected.indexes().first();
    qDebug() << "Selected cell rawValue" << _gridData[selectedIndex.row()][selectedIndex.column()].rawValue;
    Q_EMIT tableViewDidSelectCell(_gridData[selectedIndex.row()][selectedIndex.column()].rawValue);
}

void TableViewController::onTableViewItemChanged(QStandardItem *item)
{
    QString text = item->text();

    CellData cellData;
    cellData.rawValue = text;
    cellData.isFormula = (text[0] == '=');

    PythonInterpreter* interpreter = InterpreterHandler::instance()->getInterpreter();
    if (cellData.isFormula) {
        cellData.value = interpreter->run(text.mid(1, text.length() - 1));
    } else {
        cellData.value = text;
    }
    QString varName = QString('A' + item->column()) + QString::number(item->row() + 1);
    interpreter->addVariable(varName, cellData.value);

    _gridData[item->row()][item->column()] = cellData;

    // отписываемся, чтобы повторно не вызвало данный метод
    QObject::disconnect(_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onTableViewItemChanged(QStandardItem*)));
    item->setText(cellData.value);
    QObject::connect(_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onTableViewItemChanged(QStandardItem*)));

    Q_EMIT tableViewCellDidEndEditing(text);
}
