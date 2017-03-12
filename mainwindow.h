#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include "memoryallocation.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int choose;
    MemoryAllocation target,original;
    int flag;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MemoryAllocation TakeInputs();
    void DrawHoles(MemoryAllocation me);
    void DrawProc(MemoryAllocation me);

private slots:
    void on_StartBut_clicked();

    void on_ShowProcesses_clicked();

    void on_FirstFit_clicked();

    void on_BestFit_clicked();

    void on_WorstFit_clicked();

    void on_DeAloocat_clicked();

    void on_Insert_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
