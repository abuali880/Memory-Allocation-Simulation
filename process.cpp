#include "process.h"

process::process()
{
    taken = false;
}

void process::SetName(QString n)
{
    name = n;
}

void process::SetSize(int s)
{
    size = s;
}

QString process::GetName()
{
    return name;
}

int process::GetSize()
{
    return size;
}

void process::SetTaken(bool b)
{
    taken = b;
}
