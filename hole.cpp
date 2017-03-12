#include "hole.h"

hole::hole()
{
    full = false;
}

int hole::GetSize()
{
    return size;
}

void hole::SetIndex(int i)
{
    index = i;
}

int hole::GetIndex()
{
    return index;
}

void hole::SetStart(int s)
{
    start = s;
    end = start + size;
}

void hole::SetEmpty(int em)
{
    empty = em;
}

void hole::SetSize(int d)
{
    size = d;
}

void hole::AddJoined(process p)
{
    joined.push_back(p);
}

QVector<process> hole::GetJoined()
{
    return joined;
}

void hole::SetJoined(QVector<process> j)
{
    joined = j;
}

void hole::SetEnd(int e)
{
    end = e;
}

void hole::SetFull(bool b)
{
    full = b;
}

bool hole::GetFull()
{
    return full;
}

int hole::GetEmpty()
{
    return empty;
}

int hole::GetStart()
{
    return start;
}

int hole::GetEnd()
{
    return end;
}
