#ifndef CELLDATA_H
#define CELLDATA_H

#include <QString>

struct CellData
{
    QString value;
    QString rawValue;
    bool isFormula;
};

#endif // CELLDATA_H
