#ifndef CELLDATA_H
#define CELLDATA_H

#include <QString>

struct CellData
{
    CellData() {
        isFormula = false;
    }

    QString value;
    QString rawValue;
    bool isFormula;
};

#endif // CELLDATA_H
