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

    scene1 = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene1); //give the grid to the graphics view -Paul

    scene2 = new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene2); //give the timeline to the graphics view -Paul

    //GridSquare **square = new GridSquare*[G_COL];  //Type is GridSquare, square is object
    for (int i = 0; i < G_COL; ++i)
    {
        square[i] = new GridSquare[G_ROW];
        square2[i] = new TimelineGrid[G_ROW];
    }

    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            square[x][y].x = (25*x);
            square[x][y].y = (25*y);
            square2[x][y].x = (10*x); //timeline magic about to happen here -P
            square2[x][y].y = (10*y); //will add the magic soon -P
            scene1->addItem(&square[x][y]);
            scene2->addItem(&square2[x][y]); //timeline testing here -P
        }
    }

    ColorWheel *wheel = new ColorWheel;
    QSpinBox *spinbox = new QSpinBox;
    connect(wheel, SIGNAL(colorChange(QColor)), spinbox, SLOT(on_spinBox_editingFinished()));

    //Start the FrameData nonsense -P
    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // set grid size

    //t_FrameData FrameData;  // THE frame data (this is in mainwindow.h) -P
    FrameData.r = G_ROW;
    FrameData.c = G_COL;
    FrameList framelist(G_ROW, G_COL); // linked list for frame data. r c for print function


    FrameData.ID = FrameID++;
    FrameData.durration = 0.20;
    FrameData.data = create_RGB(G_ROW, G_COL);  // Generate new rgb_data arrary
    fillFrame2(FrameData, 100, 100, 100);             // Clear initial frame
    framelist.AddTail(FrameData);               // add this frameData to linked list

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

    gridToFrameData(); //on every click lol -P
    updateTimeline(); //lol -P
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

void MainWindow::gridToFrameData() //stitching rubbish -P
{
    //fill the FrameData with GUI grid data here -P
    for (int i = 0; i < G_ROW; i++){
        for (int j = 0; j < G_COL; j++){
            //qDebug() << FrameData.data[i][j].R;
            //qDebug() << square[i][j].square_RGB.red();
            FrameData.data[i][j].R = square[j][i].square_RGB.red(); //wowzers, that's stitched together -P
            FrameData.data[i][j].G = square[j][i].square_RGB.green(); //yes, i and j are switched in square. Get over it -P
            FrameData.data[i][j].B = square[j][i].square_RGB.blue(); //-P
        }
    }
}

void MainWindow::FrameDataToGrid()
{
    //fill the GUI grid with FrameData here -P
    for (int i = 0; i < G_ROW; i++){
        for (int j = 0; j < G_COL; j++){
            //wowzers, the stitching -P
            square[j][i].square_RGB.setRgb(FrameData.data[i][j].R, FrameData.data[i][j].G, FrameData.data[i][j].B, 255);
            //yes i and j still switched in frame
        }
    }
}

void MainWindow::updateTimeline()
{
    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            square2[x][y].square_RGB = square[x][y].square_RGB; //grab the colors from the real grid
            square2[x][y].update();
        }
    }
}

