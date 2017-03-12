#include "memoryallocation.h"
bool cmp( hole & a, hole & b)
{
    return a.GetSize() < b.GetSize();
}
bool cmpEmpty( hole & a, hole & b)
{
    return a.GetEmpty() < b.GetEmpty();
}
bool cmpIndex(hole & a, hole & b)
{
    return a.GetIndex() < b.GetIndex();
}
bool cmpG( hole & a, hole & b)
{
    return a.GetSize() > b.GetSize();
}
bool cmpEmptyG( hole & a, hole & b)
{
    return a.GetEmpty() > b.GetEmpty();
}

MemoryAllocation::MemoryAllocation()
{

}

void MemoryAllocation::ClearAll()
{
    pro.clear();
    ho.clear();
}

void MemoryAllocation::AddProcess(process p)
{
    pro.push_back(p);
}

void MemoryAllocation::AddHole(hole h)
{
    ho.push_back(h);
}

void MemoryAllocation::SetSize(int s)
{
    MemSize = s;
}

void MemoryAllocation::SetHoles(QVector<hole> ve)
{
    ho = ve;
}
QVector<hole> MemoryAllocation :: GetHoles()
{
    return ho;
}

QVector<process> MemoryAllocation::GetPros()
{
    return pro;
}

MemoryAllocation MemoryAllocation::FirstFit()
{
    QVector<process>::iterator i;
    QVector<hole>::iterator k;
    int HoleEmpty,ProSize;
    for(i = pro.begin();i!=pro.end();++i)
    {
        for(k = ho.begin();k!=ho.end();++k)
        {
            HoleEmpty = k->GetEmpty();
            ProSize = i->GetSize();
            if (ProSize <= HoleEmpty)
            {
                i->SetTaken(true);
                k->SetFull(true);
                k->AddJoined(*i);
                k->SetEmpty(HoleEmpty - ProSize);
                goto next;
            }
        }
        next:;
    }
    return *this;
}

MemoryAllocation MemoryAllocation::InsertFirst(process p)
{
    QVector<hole>::iterator k;
    AddProcess(p);
    for(k = ho.begin();k!=ho.end();++k)
    {
        if(p.GetSize() <= k->GetEmpty())
        {
            k->SetFull(true);
            p.SetTaken(true);
            k->AddJoined(p);
            k->SetEmpty(k->GetEmpty() - p.GetSize());
            break;
        }
    }
    return *this;
}

MemoryAllocation MemoryAllocation::InsertBest(process p)
{
    qSort(ho.begin(),ho.end(),cmpEmpty);
    InsertFirst(p);
    qSort(ho.begin(),ho.end(),cmpIndex);
    return *this;
}

MemoryAllocation MemoryAllocation::InsertWorst(process p)
{
    qSort(ho.begin(),ho.end(),cmpEmptyG);
    InsertFirst(p);
    qSort(ho.begin(),ho.end(),cmpIndex);
    return *this;
}


process* MemoryAllocation::FindProcess(QString s)
{
    QVector <process>::iterator i;
    for(i = pro.begin();i!=pro.end();++i)
    {
        if(i->GetName() == s) return i;
    }
    process nul;
    nul.SetSize(0);
    nul.SetName(" ");
    return NULL;
}

QString MemoryAllocation::GetProNames()
{
    QVector<process>::iterator i;
    QString output;
    for(i=pro.begin();i!=pro.end();i++)
    {
        output += i->GetName();
        if(i != pro.end()) output += "\n";
    }
    return output;
}

QString MemoryAllocation::GetProSize()
{
    QVector<process>::iterator i;
    QString output;
    for(i=pro.begin();i!=pro.end();i++)
    {
        output += QString::number(i->GetSize());
        if(i != pro.end()) output += "\n";
    }
    return output;
}
MemoryAllocation MemoryAllocation :: DeAllocation(process p)
{
    QVector<process> join,pre;
    QVector<process>::iterator i,m;
    QVector<hole>::iterator k,j,l;
    for(k = ho.begin();k!=ho.end();++k)
    {
        int indicator=0;
        int address = k->GetStart();
        if(k->GetFull())
        {
            join = k->GetJoined();
            for(i = join.begin() ; i!= join.end() ;)
            {
                if(i->GetName() == p.GetName())
                {
                    hole h,pe,af;
                    pe.SetSize(indicator);
                    pe.SetEmpty(0);
                    pe.SetStart(address);
                    pe.SetFull(true);
                    pe.SetJoined(pre);
                    pe.SetFull(true);
                    h.SetSize(p.GetSize());
                    h.SetEmpty(p.GetSize());
                    h.SetStart(address+indicator);
                    h.SetFull(false);
                    af.SetSize(k->GetSize() - p.GetSize() - indicator);
                    af.SetEmpty(k->GetEmpty());
                    af.SetStart(address + indicator + p.GetSize());
                    if(join.empty()) af.SetFull(false);
                    else af.SetFull(true);
                    i = join.erase(i);
                    af.SetJoined(join);
                    k = ho.erase(k);
                    k = ho.insert(k,af);
                    k = ho.insert(k,h);
                    k = ho.insert(k,pe);
                    address+=p.GetSize();
                    goto end;
                }
                else
                {
                    pre.push_back(*i);
                    indicator+=i->GetSize();
                    i = join.erase(i);
                }
            }
            pre.clear();
        }
    }
    end:;
    for(m=pro.begin();m!=pro.end();)
    {
        if(m->GetName() == p.GetName()) m = pro.erase(m);
        else m++;
    }
    for(j = ho.begin();j!=ho.end();)
    {
        l=j;
        l++;
        if(j->GetEnd() == l->GetStart() && j->GetJoined().empty() && l->GetJoined().empty())
        {
            hole ss;
            ss.SetSize(j->GetSize()+l->GetSize());
            ss.SetEmpty(j->GetEmpty()+l->GetEmpty());
            ss.SetStart(j->GetStart());
            ss.SetFull(false);
            j = ho.erase(j);
            j = ho.erase(j);
            j = ho.insert(j,ss);
            if(j->GetSize() == ho.back().GetSize() && j->GetStart() == ho.back().GetStart() && j->GetEnd() == ho.back().GetEnd() && j->GetEmpty() == ho.back().GetEmpty())
                break;
        }
        else ++j;
    }
    return *this;
}

QString MemoryAllocation::ShowState()
{
    QVector<process>::iterator i ;
    QVector<hole>::iterator k;
    QString result;
    result+="Current Processes: \n";
    for(i=pro.begin();i!=pro.end();i++)
    {
        result+= i->GetName() + " : " + QString::number(i->GetSize()) + " K \n" ;
    }
    result+="---------------------\nCurrent Holes: \n";
    for(k=ho.begin();k!=ho.end();k++)
    {
        result+=QString::number(k->GetSize()) + " at Addr. " +QString::number(k->GetStart()) + "\n" ;
    }
    return result;
}

MemoryAllocation MemoryAllocation::BestFit()
{
    qSort(ho.begin(),ho.end(),cmp);
    FirstFit();
    qSort(ho.begin(),ho.end(),cmpIndex);
    return *this;
}

MemoryAllocation MemoryAllocation::WorstFit()
{
    qSort(ho.begin(),ho.end(),cmpG);
    FirstFit();
    qSort(ho.begin(),ho.end(),cmpIndex);
    return *this;
}

