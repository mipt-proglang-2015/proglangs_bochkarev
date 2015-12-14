#ifndef PYTHONINTERPRETER_H
#define PYTHONINTERPRETER_H
#include <QString>

extern "C"
{
#include <Python.h>
}

#include <map>
#include <QObject>


class PythonInterpreter: public QObject
{
    Q_OBJECT
public:
    explicit PythonInterpreter(QObject *parent = 0);

    QString run(const QString &program);
    void addVariable(const QString& name, const QString& value);

Q_SIGNALS:
    void pythonInterpreterDidFail(const QString& errorMsg);
private:
    QString evaluateProgram(const QString &program);

    static std::map<QString, QString> _variables;
    static PyObject* _mainModule;
    static PyObject* _moduleDict;
};

#endif // PYTHONINTERPRETER_H
