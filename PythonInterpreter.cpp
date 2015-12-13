#include "PythonInterpreter.h"

#include <Python.h>

PythonInterpreter* PythonInterpreter::_instance = 0;

PythonInterpreter* PythonInterpreter::instance()
{
    if (_instance == 0) {
        _instance = new PythonInterpreter();
        Py_Initialize();
    }
    return _instance;
}

PythonValue PythonInterpreter::runSimpleString(const QString& string) const
{
    PyRun_SimpleString("from math import *\n");
    QString evalString = "result = str(" + string + ")";
    PyRun_SimpleString( evalString.toStdString().c_str() );

    PyObject* module = PyImport_AddModule( "__main__" );
    assert(module);

    PyObject* dict = PyModule_GetDict( module );
    assert(dict);

    PyObject* result = PyDict_GetItemString( dict, "result" );

    char* retString = 0;
    if (result == NULL) {
        retString = "#ERROR";

        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);
        std::cout << PyString_AsString( pvalue ) << std::endl;
    } else if (PyString_Check(result)) {
        retString = PyString_AsString( result );
    }

    PythonValue value;
    value.stringValue = retString;
    return value;
}
