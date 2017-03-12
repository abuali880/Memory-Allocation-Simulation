#ifndef MEMORYALLOCATION_H
#define MEMORYALLOCATION_H

#include <QMainWindow>
#include "process.h"
#include "hole.h"
#include <QtAlgorithms>
#include <QVector>
#include <QPair>

class MemoryAllocation
{
    QVector <process> pro;
    QVector <hole> ho;
    int MemSize;

public:
    MemoryAllocation();
    void ClearAll();
    void AddProcess(process p);
    void AddHole(hole h);
    void SetSize(int s);
    void SetHoles(QVector<hole> ve);
    bool Found(hole *h);
    QVector<hole> GetHoles();
    QVector<process> GetPros();
    MemoryAllocation FirstFit();
    MemoryAllocation InsertFirst(process p);
    MemoryAllocation InsertBest(process p);
    MemoryAllocation InsertWorst(process p);
    process *FindProcess(QString s);
    QString GetProNames();
    QString GetProSize();
    MemoryAllocation BestFit();
    MemoryAllocation WorstFit();
    MemoryAllocation DeAllocation(process p);
    QString ShowState();
};

#endif // MEMORYALLOCATION_H
