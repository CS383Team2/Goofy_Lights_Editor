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

    /*
     * ok, don't want to mess around with loops and actually use my brain,
     * so here are 16 GridSquares all created and places individually.
     * -Paul.....
     */

    square1 = new GridSquare();
    square2 = new GridSquare();
    square3 = new GridSquare();
    square4 = new GridSquare();
    square5 = new GridSquare();
    square6 = new GridSquare();
    square7 = new GridSquare();
    square8 = new GridSquare();
    square9 = new GridSquare();
    square10 = new GridSquare();
    square11 = new GridSquare();
    square12 = new GridSquare();
    square13 = new GridSquare();
    square14 = new GridSquare();
    square15 = new GridSquare();
    square16 = new GridSquare();
    square1->x = 0;
    square1->y = 0;
    square2->x = 0;
    square2->y = 25;
    square3->x = 0;
    square3->y = 50;
    square4->x = 0;
    square4->y = 75; //end row
    square5->x = 25;
    square5->y = 0;
    square6->x = 25;
    square6->y = 25;
    square7->x = 25;
    square7->y = 50;
    square8->x = 25;
    square8->y = 75; //end row
    square9->x = 50;
    square9->y = 0;
    square10->x = 50;
    square10->y = 25;
    square11->x = 50;
    square11->y = 50;
    square12->x = 50;
    square12->y = 75; //end row
    square13->x = 75;
    square13->y = 0;
    square14->x = 75;
    square14->y = 25;
    square15->x = 75;
    square15->y = 50;
    square16->x = 75;
    square16->y = 75; //end row
    scene->addItem(square1);
    scene->addItem(square2);
    scene->addItem(square3);
    scene->addItem(square4);
    scene->addItem(square5);
    scene->addItem(square6);
    scene->addItem(square7);
    scene->addItem(square8);
    scene->addItem(square9);
    scene->addItem(square10);
    scene->addItem(square11);
    scene->addItem(square12);
    scene->addItem(square13);
    scene->addItem(square14);
    scene->addItem(square15);
    scene->addItem(square16);

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
