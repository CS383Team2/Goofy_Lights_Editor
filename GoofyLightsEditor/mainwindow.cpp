#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileOperations.h"
#include "FrameList.h"
#include <QFileDialog>
#include <QtDebug>
#include <QWidget>
#include <sizedialog.h>
#include <globals.h> //G_ROW and G_COL
#include <FrameManipulation.h>

long FrameID = 0; //-P
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

    //Start the FrameData nonsense -P
    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // set grid size
    int r = G_ROW;
    int c = G_COL;
    t_RGB ** rgb_data;

    //t_FrameData FrameData;  // THE frame data (this is in mainwindow.h) -P
    FrameData.r = r;
    FrameData.c = c;
    FrameList frames(r, c); // linked list for frame data. r c for print function

    //Frame 0
    // Generate new rgb_data arrary
    rgb_data = create_RGB(r, c);

    // fill rgb_data for Frame 0
    //unsigned short color = 0;   // arbritrary data
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            rgb_data[i][j].R = 0;
            rgb_data[i][j].G = 0;
            rgb_data[i][j].B = 0;
        }
    }
    FrameData.ID = FrameID++;
    FrameData.durration = 0.20;
    FrameData.data = rgb_data;
    frames.AddTail(FrameData);  // add this frameData to linked list
    rgb_data  = NULL; // disconnect this pointer from rgb_data


    // next frame Frame 1
    // Generate new rgb_data arrary
    //rgb_data = create_RGB(r, c);
    //...
    //...

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


void MainWindow::mousePressEvent(QMouseEvent *event) //any time the window is clicked inside of, lol -P
{
    ui->spinBox->setValue(G_RED); //-P
    ui->spinBox_2->setValue(G_GREEN);
    ui->spinBox_3->setValue(G_BLUE); //-P

    //gridToFrameDate(); //on every click lol -P SEG FAULT on  FrameData.data[i][j].R = square[i][j].square_RGB.red();
}


void MainWindow::on_pushButton_20_clicked() //Fill Frame
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

void MainWindow::on_pushButton_21_released() //Clear Frame
{
    G_RED = temp_R;
    G_GREEN = temp_G;
    G_BLUE = temp_B;

    ui->spinBox->setValue(G_RED); //-P
    ui->spinBox_2->setValue(G_GREEN);
    ui->spinBox_3->setValue(G_BLUE); //-P
}

void MainWindow::on_pushButton_21_pressed() //Clear Frame
{
    temp_R = G_RED;
    temp_G = G_GREEN;
    temp_B = G_BLUE;
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
            square[x][y].update(); //Fill that frame son -P
        }
    }


    //do this:

    fillFrame2(FrameData, 0, 0, 0); //not tested yet -P
}

void MainWindow::gridToFrameDate() //stitching rubbish -P
{
    //fill the FrameData with GUI grid data here -P
    for (int i = 0; i < G_ROW; i++){
        for (int j = 0; j < G_COL; j++){
            FrameData.data[i][j].R = square[i][j].square_RGB.red(); //wowzers, that's stitched together -P
            FrameData.data[i][j].G = square[i][j].square_RGB.green();
            FrameData.data[i][j].B = square[i][j].square_RGB.blue(); //-P
        }
    }
}

void MainWindow::FrameDateToGrid()
{
    //fill the GUI grid with FrameData here -P
    for (int i = 0; i < G_ROW; i++){
        for (int j = 0; j < G_COL; j++){
            //wowzers, the stitching -P
            square[i][j].square_RGB.setRgb(FrameData.data[i][j].R, FrameData.data[i][j].G, FrameData.data[i][j].B, 255);
        }
    }
}

