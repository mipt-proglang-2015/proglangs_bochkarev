#ifndef CELLDATA_H
#define CELLDATA_H

#include <QString>

class CellData
{
public:
    CellData();

    QString value;
    QString rawValue;
    bool isEditing;
};

#endif // CELLDATA_H
