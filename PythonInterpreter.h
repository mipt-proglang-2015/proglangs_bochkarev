#ifndef PYTHONINTERPRETER_H
#define PYTHONINTERPRETER_H

#include <map>
#include "common.h"

enum class PyValueType: int {
    PyValueTypeInt,
    PyValueTypeFloat,
    PyValueTypeBool,
    PyValueTypeLong,
};

struct PythonValue
{
    PyValueType type;

    int intValue;
    long long longValue;
    float floatValue;
    bool boolValue;

    QString stringValue;
};

class PythonInterpreter
{
public:
    static PythonInterpreter* instance();

    QString loadProgram(const QString& path);
    PythonValue evaluateFunction(const QString& method);

    PythonValue runSimpleString(const QString& string) const;

private:
    PythonInterpreter(){};
    ~PythonInterpreter() {delete _instance;}

    static PythonInterpreter* _instance;
};

#endif // PYTHONINTERPRETER_H
