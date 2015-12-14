#ifndef INTERPRETERHANDLER_H
#define INTERPRETERHANDLER_H

extern "C"
{
#include <Python.h>
#include <frameobject.h>
}

#include <map>
#include <QObject>

class PythonInterpreter;

class InterpreterHandler : public QObject
{
    Q_OBJECT
public:
    static InterpreterHandler* instance();
    static PythonInterpreter* getInterpreter();
    static void destroyInterpreter();

    static int trace(PyObject*, PyFrameObject*, int what, PyObject *arg);

Q_SIGNALS:
    void pythonInterpreterDidFail(const QString& errorMsg);
public Q_SLOTS:
    void onPythonInterpreterDidFail(const QString& errorMsg);
private:
    explicit InterpreterHandler(QObject *parent = 0);

    static std::map<PyThreadState*, PythonInterpreter*> _interpreters;
    static InterpreterHandler* _instance;
};

#endif // INTERPRETERHANDLER_H
