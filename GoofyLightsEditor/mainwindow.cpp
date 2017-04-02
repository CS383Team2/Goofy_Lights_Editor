#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileOperations.h"
#include "FrameList.h"
#include <QFileDialog>
#include <QtDebug>
#include <QWidget>
#include <sizedialog.h>
#include <globals.h> //G_ROW and G_COL


int temp_R, temp_G, temp_B, temp_A; //yeah.... -P


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene); //give the grid to the graphics view -Paul

    //GridSquare **square = new GridSquare*[G_COL];  //Type is GridSquare, square is object
    for (int i = 0; i < G_COL; ++i)
    {
        square[i] = new GridSquare[G_ROW];
    }

    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            square[x][y].x = (25*x);
            square[x][y].y = (25*y);
            scene->addItem(&square[x][y]);
        }
    }
    ColorWheel *wheel = new ColorWheel;
    QSpinBox *spinbox = new QSpinBox;
    connect(wheel, SIGNAL(colorChange(QColor)), spinbox, SLOT(on_spinBox_editingFinished()));

}

MainWindow::~MainWindow()
{
    delete ui;
    exit(0); //WHOA fixed the SIGABRT on Linux -P
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Project"), "",
            tr("Project (*.proj);;All Files (*)"));
    FrameList frameList = FrameList(10,10);
    t_FrameData frameData;
    frameList.AddTail(frameData);

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


void MainWindow::on_spinBox_editingFinished()
{
    //crap -P
    G_RED = ui->spinBox->value();
}

void MainWindow::on_spinBox_2_editingFinished()
{
    G_GREEN = ui->spinBox_2->value(); //-P
}

void MainWindow::on_spinBox_3_editingFinished()
{
    G_BLUE = ui->spinBox_3->value();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    ui->spinBox->setValue(G_RED); //-P
    ui->spinBox_2->setValue(G_GREEN);
    ui->spinBox_3->setValue(G_BLUE); //-P
}


void MainWindow::on_pushButton_20_clicked()
{
    //first let's update the GRAPHICAL EYBALL STIMILATION GRID for motivation -P
    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            square[x][y].Selected = true;
            square[x][y].update(); //Fill that frame son -P
        }
    }

    //do this:

    //fillFrame(t_FrameData &d, t_RGB rgb_fill) //do this later -P
}

void MainWindow::on_pushButton_21_clicked()
{


}

void MainWindow::on_pushButton_21_released()
{
    G_RED = temp_R;
    G_GREEN = temp_G;
    G_BLUE = temp_B;
    G_ALPHA = temp_A;

    ui->spinBox->setValue(G_RED); //-P
    ui->spinBox_2->setValue(G_GREEN);
    ui->spinBox_3->setValue(G_BLUE); //-P
}

void MainWindow::on_pushButton_21_pressed()
{
    temp_R = G_RED;
    temp_G = G_GREEN;
    temp_B = G_BLUE;
    temp_A = G_ALPHA;
    //first let's update the GRAPHICAL EYBALL STIMILATION GRID for motivation -P
    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            square[x][y].Selected = true;
            //BLACK
            G_RED = 0;
            G_GREEN = 0;
            G_BLUE = 0;
            G_ALPHA = 255;
            square[x][y].update(); //Fill that frame son -P
        }
    }


    //do this:

    //clearFrame????(t_FrameData &d, t_RGB rgb_fill) //do this later -P
}
