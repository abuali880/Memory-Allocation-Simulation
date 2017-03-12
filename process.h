#ifndef PROCESS_H
#define PROCESS_H

#include <QWidget>
#include <QString>
class process
{
    QString name;
    int size;
    bool taken;
public:
    process();
    void SetName(QString n);
    void SetSize(int s);
    QString GetName();
    int GetSize();
    void SetTaken(bool b);
};

#endif // PROCESS_H
