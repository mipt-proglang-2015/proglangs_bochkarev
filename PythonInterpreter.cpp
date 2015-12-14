#include <QDebug>

#include "PythonInterpreter.h"
#include "InterpreterHandler.h"
#include "Exception.h"

std::map<QString, QString> PythonInterpreter::_variables = std::map<QString, QString>();
PyObject* PythonInterpreter::_mainModule = 0;
PyObject* PythonInterpreter::_moduleDict = 0;

PythonInterpreter::PythonInterpreter(QObject *parent) : QObject(parent)
{
    Py_Initialize();
    _mainModule = PyImport_AddModule("__main__");
    _moduleDict = PyModule_GetDict(_mainModule);
    PyRun_SimpleString("from math import *\n");
    for (auto var: _variables) {
        PyRun_SimpleString((var.first + "=" + var.second + "\n").toStdString().c_str());
    }
    PyEval_SetTrace(InterpreterHandler::trace, NULL);

    QObject::connect(this, SIGNAL(pythonInterpreterDidFail(QString)),
                     InterpreterHandler::instance(), SLOT(onPythonInterpreterDidFail(QString)));
}

QString PythonInterpreter::evaluateProgram(const QString &program)
{
    const QByteArray utf8_program = program.toUtf8();

    PyObject* code = Py_CompileString(utf8_program.constData() , "" , Py_eval_input);
    if (!code) throw Exception();

    PyObject* evaluationResult = PyEval_EvalCode(code, _moduleDict, _moduleDict);
    if (!evaluationResult) throw Exception();

    PyObject* programOut = PyObject_Repr(evaluationResult);
    wchar_t* outBuffer = PyUnicode_AsWideCharString(programOut, NULL);
    Py_DECREF(programOut);
    Py_DECREF(evaluationResult);

    return QString::fromWCharArray(outBuffer);
}

QString PythonInterpreter::run(const QString &program)
{
    QString result;
    try {
        result = evaluateProgram(program);
    } catch (Exception& e) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);
        wchar_t* outBuffer = pvalue ? PyUnicode_AsWideCharString(pvalue, NULL) : 0;
        QString errorMsg = outBuffer ? QString::fromWCharArray(outBuffer) : "Syntax Error!";
        Q_EMIT pythonInterpreterDidFail(errorMsg);
        result = "#ERROR";
    }

    InterpreterHandler::destroyInterpreter();
    return result;
}

void PythonInterpreter::addVariable(const QString& name, const QString& value)
{
    QString castedValue = value;
    bool isNumber;
    value.toLong(&isNumber);
    if (!isNumber) {
        value.toDouble(&isNumber);
        if (!isNumber) {
            castedValue = "'" + castedValue + "'";
        }
    }

    _variables[name] = castedValue;

    qDebug() << "Added variable: " + name + "=" + castedValue;
}
