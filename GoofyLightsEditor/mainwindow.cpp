#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileOperations.h"
#include "FrameList.h"
#include <QFileDialog>
#include <QtDebug>
#include <QWidget>
//#include <vector> //all sorts of fancy -P


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene); //give the grid to the graphics view -Paul

    int ROWS = 10; //switched these on accident lol
    int COLS = 10;

    GridSquare **square = new GridSquare*[ROWS];  //Type is GridSquare, square is object
    for (int i = 0; i < ROWS; ++i)
    {
        square[i] = new GridSquare[COLS];
    }

    for(int x=0; x<ROWS; x++)
    {
        for(int y=0; y<COLS; y++)
        {
            square[x][y].x = (25*x);
            square[x][y].y = (25*y);
            scene->addItem(&square[x][y]);
        }
    }

    delete square; //yeah need to fix this to fix the signal at on close -P


}

MainWindow::~MainWindow()
{
    // delete square?!?!?!??!?!!!??! -P
    delete ui;
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Project"), "",
            tr("Project (*.proj);;All Files (*)"));
    FrameList frameList = FrameList(10,10);
    t_FrameData frameData;
    frameList.AddNode(frameData);

    FileOperations::SaveToFile(frameList,fileName);
    qDebug() << "Returned safely";
}

FrameList MainWindow::on_actionOpenProject_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Project"), "",
            tr("Project (*.proj);;All Files (*)"));

    return FileOperations::LoadFromFile(fileName);
}
