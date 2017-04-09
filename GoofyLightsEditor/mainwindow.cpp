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

    gridScene = new QGraphicsScene(this);
    ui->gView_Grid->setScene(gridScene); //give the grid to the graphics view -Paul

    timelineScene = new QGraphicsScene(this);
    ui->gView_Timeline->setScene(timelineScene); //give the timeline to the graphics view -Paul

    //GridSquare **square = new GridSquare*[G_COL];  //This is now in mainwindow.h -P
    for (int i = 0; i < G_COL; ++i)
    {
        gridGridSquare[i] = new GridSquare[G_ROW];
        timelineTimelineGrid[i] = new TimelineGrid[G_ROW];
    }

    int gridScale = 22*G_SCALE;
    int timelineScale = 4*G_SCALE;
    int g_SPACING = 3; //grid spacing woohooo -P
    int t_SPACING = 2; //timeline spacing woohooo -P

    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            gridGridSquare[x][y].x = (x*gridScale + x*g_SPACING);
            gridGridSquare[x][y].y = (y*gridScale + y*g_SPACING);
            timelineTimelineGrid[x][y].x = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
            timelineTimelineGrid[x][y].y = (y*timelineScale + y*t_SPACING); //will add the magic soon -P
            gridScene->addItem(&gridGridSquare[x][y]);
            timelineScene->addItem(&timelineTimelineGrid[x][y]); //timeline testing here -P
        }
    }

    ColorWheel *wheel = new ColorWheel;
    QSpinBox *spinbox = new QSpinBox;
    connect(wheel, SIGNAL(colorChange(QColor)), spinbox, SLOT(on_sbox_ValueRed_editingFinished()));

    //Start the FrameData nonsense -P
    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // set grid size

    //t_FrameData FrameData;  // THE frame data (this is in mainwindow.h) -P
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
            tr("Project (*.tan);;All Files (*)"));
    FrameList frameList = FrameList(10,10); //why is this 10x10??? answer me that. -P
                                            // This was for testing purposes. There should
                                            // instead be some FrameList object that holds
                                            // our current animation so that it can be saved
                                            // and loaded to. -T
    t_FrameData frameData;
    frameList.AddTail(frameData);

    FileOperations::SaveToFile(frameList,fileName);
    qDebug() << "Returned safely";
}

void MainWindow::on_actionOpenProject_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Project"), "",
            tr("Project (*.tan);;All Files (*)"));

    FrameList frameList;
    FileOperations::LoadFromFile(fileName, &frameList);
}


void MainWindow::on_sbox_ValueRed_editingFinished()
{
    //crap -P
    G_RED = ui->sbox_ValueRed->value();
}

void MainWindow::on_sbox_ValueGreen_editingFinished()
{
    G_GREEN = ui->sbox_ValueGreen->value(); //-P
}

void MainWindow::on_sbox_ValueBlue_editingFinished()
{
    G_BLUE = ui->sbox_ValueBlue->value();
}


void MainWindow::mousePressEvent(QMouseEvent *event) //any time the window is clicked inside of, lol -P
{
    ui->sbox_ValueRed->setValue(G_RED); //-P
    ui->sbox_ValueGreen->setValue(G_GREEN);
    ui->sbox_ValueBlue->setValue(G_BLUE); //-P


    gridToFrameData(); //on every click lol -P
    updateTimeline(); //lol -P
}


void MainWindow::on_btn_FillFrame_clicked() //Fill Frame
{
    //first let's update the GRAPHICAL EYBALL STIMILATION GRID for motivation -P
    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            gridGridSquare[x][y].Selected = true;
            gridGridSquare[x][y].leftclick = true;
            gridGridSquare[x][y].update(); //Fill that frame son -P
        }
    }

    //do this:

    //fillFrame(t_FrameData &d, t_RGB rgb_fill) //do this later -P
}

void MainWindow::on_btn_ClearFrame_clicked()
{


}

void MainWindow::on_btn_ClearFrame_released() //Clear Frame
{
    G_RED = temp_R;
    G_GREEN = temp_G;
    G_BLUE = temp_B;

    ui->sbox_ValueRed->setValue(G_RED); //-P
    ui->sbox_ValueGreen->setValue(G_GREEN);
    ui->sbox_ValueBlue->setValue(G_BLUE); //-P
}

void MainWindow::on_btn_ClearFrame_pressed() //Clear Frame
{
    temp_R = G_RED;
    temp_G = G_GREEN;
    temp_B = G_BLUE;
    //first let's update the GRAPHICAL EYBALL STIMILATION GRID for motivation -P
    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            gridGridSquare[x][y].Selected = true;
            gridGridSquare[x][y].leftclick = true;
            //BLACK
            G_RED = 0;
            G_GREEN = 0;
            G_BLUE = 0;
            gridGridSquare[x][y].update(); //Fill that frame son -P
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
            //qDebug() << gridGridSquare[i][j].square_RGB.red();
            FrameData.data[i][j].R = gridGridSquare[j][i].square_RGB.red(); //wowzers, that's stitched together -P
            FrameData.data[i][j].G = gridGridSquare[j][i].square_RGB.green(); //yes, i and j are switched in square. Get over it -P
            FrameData.data[i][j].B = gridGridSquare[j][i].square_RGB.blue(); //-P
        }
    }
}

void MainWindow::FrameDataToGrid()
{
    //fill the GUI grid with FrameData here -P
    for (int i = 0; i < G_ROW; i++){
        for (int j = 0; j < G_COL; j++){
            //wowzers, the stitching -P
            gridGridSquare[j][i].square_RGB.setRgb(FrameData.data[i][j].R, FrameData.data[i][j].G, FrameData.data[i][j].B, 255);
            //yes i and j still switched in frame
        }
    }
}

void MainWindow::updateTimeline() //fix the update lag later -P
{
    for(int x=0; x<G_COL; x++)
    {
        for(int y=0; y<G_ROW; y++)
        {
            timelineTimelineGrid[x][y].square_RGB = gridGridSquare[x][y].square_RGB; //grab the colors from the real grid -P
            timelineTimelineGrid[x][y].update();
        }
    }
}

