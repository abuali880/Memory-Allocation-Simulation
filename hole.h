#ifndef HOLE_H
#define HOLE_H

#include <QWidget>
#include <QString>
#include "process.h"

class hole
{
    int start;
    int end;
    int size;
    int empty;
    bool full;
    int index;
    QVector <process> joined;
public:
    hole();
    int GetSize();
    void SetIndex(int i);
    int GetIndex();
    void SetStart(int s);
    void SetEmpty(int em);
    void SetSize(int d);
    void AddJoined(process p);
    QVector<process> GetJoined();
    void SetJoined(QVector <process> j);
    void SetEnd(int e);
    void SetFull(bool b);
    bool GetFull();
    int GetEmpty();
    int GetStart();
    int GetEnd();
};

#endif // HOLE_H
