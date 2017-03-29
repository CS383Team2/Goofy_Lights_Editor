#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileOperations.h"
#include "FrameList.h"
#include <QFileDialog>
#include <QtDebug>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene); //give the grid to the graphics view -Paul

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1); //each cell has a 1px border -Paul

    int COLS = 10; //put this somewhere else lol -Paul
    int ROWS = 10;

    int i=0;
    int j=0;
    for(i=0; i<ROWS; i++) //create rows -Paul
    {

        for(j=0; j<COLS; j++) //create columns -Paul
        {
            rectangle = scene->addRect((i*25),(j*25),20,20,blackPen,blueBrush); //(xpos,ypos,xsize,ysize,bordercolor,brushcolor) -Paul
            rectangle->setFlag(QGraphicsItem::ItemIsSelectable);
        }
    }


}

MainWindow::~MainWindow()
{
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
