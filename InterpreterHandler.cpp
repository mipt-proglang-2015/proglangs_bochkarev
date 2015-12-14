#include "InterpreterHandler.h"
#include "PythonInterpreter.h"

std::map<PyThreadState*, PythonInterpreter*> InterpreterHandler::_interpreters = std::map<PyThreadState*, PythonInterpreter*>();
InterpreterHandler* InterpreterHandler::_instance = 0;

InterpreterHandler::InterpreterHandler(QObject *parent) : QObject(parent)
{
}

InterpreterHandler* InterpreterHandler::instance()
{
    if (!_instance) {
        _instance = new InterpreterHandler(0);
    }
    return _instance;
}

PythonInterpreter* InterpreterHandler::getInterpreter()
{
    PythonInterpreter* interpreter = new PythonInterpreter();
    _interpreters[PyThreadState_Get()] = interpreter;
    return interpreter;
}

void InterpreterHandler::destroyInterpreter()
{
    PythonInterpreter* interpreter = _interpreters[PyThreadState_Get()];
    _interpreters.erase(PyThreadState_Get());
    Py_Finalize();

    QObject::disconnect(interpreter, SIGNAL(pythonInterpreterDidFail(QString)),
                     InterpreterHandler::instance(), SLOT(onPythonInterpreterDidFail(QString)));
    delete interpreter;
}

int InterpreterHandler::trace(PyObject*, PyFrameObject*, int what, PyObject *arg)
{
    PythonInterpreter* interpreter = _interpreters[PyThreadState_Get()];
    if (PyTrace_EXCEPTION == what) {
        PyObject* exception = PyTuple_GetItem(arg, 1);
        PyObject* message = PyObject_Repr(exception);
        wchar_t* msg_buffer = PyUnicode_AsWideCharString(message, NULL);
        QString errorMessage = QString::fromWCharArray(msg_buffer);
        Py_DECREF(message);
        PyMem_Free(msg_buffer);
        Q_EMIT InterpreterHandler::instance()->pythonInterpreterDidFail(errorMessage);
    }
    return 0;
}

void InterpreterHandler::onPythonInterpreterDidFail(const QString &errorMsg)
{
    Q_EMIT pythonInterpreterDidFail(errorMsg);
}
