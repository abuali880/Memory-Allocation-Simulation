#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->State->setText("\n\n          Dont Write!\n\n Your States will apear\n                 here.");
    choose = 1;
    flag = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

MemoryAllocation MainWindow :: TakeInputs()
{
    original.ClearAll();
    MemoryAllocation mem;
    process p;
    int size,inde=0;
    hole h;
    QString text = ui->Processes->toPlainText();
    QString text2 = ui->ProSize->toPlainText();
    QString text3 = ui->HoSize->toPlainText();
    QString text4 = ui->StartAdd->toPlainText();
    QStringList pieces = text.split("\n");
    QStringList pieces2 = text2.split("\n");
    QStringList pieces3 = text3.split("\n");
    QStringList pieces4 = text4.split("\n");
    QString proces =  ui->NuPro->toPlainText();
    int ProcessNumber = proces.toInt();
    int Count1 = pieces.size();
    int Count2 = pieces3.size();
    /*if(Count1 > ProcessNumber && flag ==0)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Warning","You exceed the entered number of processes, but you can still continue!");
        messageBox.setFixedSize(0,0);
        flag == 1;
    }*/
    if(pieces.size() > pieces2.size()) Count1 = pieces2.size();
    if(pieces3.size() > pieces4.size()) Count2 = pieces4.size();
    for(int i=0 ; i<Count1 ; i++)
    {
        p.SetName(pieces[i]);
        size = pieces2[i].toInt();
        p.SetSize(size);
        original.AddProcess(p);
    }
    for(int i = 0 ; i <Count2 ; i++)
    {
        size = pieces3[i].toInt();
        h.SetSize(size);
        h.SetEmpty(size);
        h.SetStart(pieces4[i].toInt());
        h.SetIndex(inde);
        original.AddHole(h);
        inde++;
    }
    return mem;
}
void MainWindow :: DrawHoles(MemoryAllocation me)
{
    scene->clear();
    TakeInputs();
    MemoryAllocation mem = me;
    int x=0,y =0,hh=150,w;
    QVector<hole> hol;
    hol = mem.GetHoles();
    QVector<hole>::iterator i;
    QBrush greenBru(Qt::gray);
    QPen pen;
    pen.setWidth(1);
    for(i=hol.begin();i!=hol.end();++i)
    {
        w = i->GetSize();
        scene->addRect(x,y,w,hh,pen,greenBru);
        scene->addSimpleText(QString::number(i->GetStart()))->setPos(x,y+hh);
        scene->addSimpleText(QString::number(i->GetSize()) + " K")->setPos(x+(w/2),y+120);
        x+=w;
    }

}
void MainWindow :: DrawProc(MemoryAllocation me)
{
    TakeInputs();
    MemoryAllocation mem = me;
    QVector<hole> hol;
    QVector<process> proo;
    QVector<hole>::iterator i;
    QVector<process>::iterator k;
    QPen pen1;
    pen1.setWidth(0);
    int x=0,y = 0,hh=120,w;
    hol = mem.GetHoles();
    proo = mem.GetPros();
    QBrush redBru(Qt::darkCyan);
    for(i=hol.begin();i!=hol.end();++i)
    {
        if(i->GetFull())
        {
            QVector<process> join = i->GetJoined();
            for(k=join.begin();k!=join.end();++k)
            {
                w = k->GetSize();
                QPoint p(x + 3,y+50);
                scene->addRect(x,y,w,hh,pen1,redBru);
                scene->addSimpleText(k->GetName() + "\n" + QString::number(k->GetSize()) + " K")->setPos(p);
                x+=w;
            }
        }
        x+= i->GetEmpty();
    }
}

void MainWindow::on_StartBut_clicked()
{
    TakeInputs();
    DrawHoles(original);
    ui->State->setText(target.ShowState());
}

void MainWindow::on_ShowProcesses_clicked()
{
    TakeInputs();
    DrawHoles(original);
    MemoryAllocation mem1;
    if (choose == 1) target = original.FirstFit();
    else if (choose == 2) target = original.BestFit();
    else if (choose== 3) target = original.WorstFit();
    DrawProc(target);
    flag = 0;
    ui->State->setText(target.ShowState());
}

void MainWindow::on_FirstFit_clicked()
{
    choose = 1;
}

void MainWindow::on_BestFit_clicked()
{
    choose = 2;
}

void MainWindow::on_WorstFit_clicked()
{
    choose = 3;
}

void MainWindow::on_DeAloocat_clicked()
{
    //DrawHoles(original);
   /* if(flag == 0)
    {
        if (choose == 1) target = original.FirstFit();
        else if (choose == 2) target = original.BestFit();
        else if (choose== 3) target = original.WorstFit();
        flag = 1;
    }*/
    QString deleted = ui->DeletedP->toPlainText();
    process *deletedPp = target.FindProcess(deleted);
    if(deletedPp == NULL)
    {
        ui->DeletedP->setText("");
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Process Not Found!");
        messageBox.setFixedSize(0,0);
    }
    else
    {
        process deletedP = * deletedPp;
        target = target.DeAllocation(deletedP);
        DrawHoles(target);
        DrawProc(target);
        ui->DeletedP->setText("");
        ui->Processes->setText(target.GetProNames());
        ui->ProSize->setText(target.GetProSize());
    }
    ui->State->setText("");
    ui->State->setText(target.ShowState());
}


void MainWindow::on_Insert_clicked()
{
    QString insertedN = ui->InsertedName->toPlainText();
    int InsertedS = ui->InsertedSize->toPlainText().toInt();
    process p;
    p.SetName(insertedN);
    p.SetSize(InsertedS);
    if(choose == 1) target.InsertFirst(p);
    else if (choose == 2) target.InsertBest(p);
    else if (choose == 3) target.InsertWorst(p);
    DrawHoles(target);
    DrawProc(target);
    ui->InsertedName->setText("");
    ui->InsertedSize->setText("");
    ui->State->setText(target.ShowState());
}
