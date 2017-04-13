#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileOperations.h"
#include "FrameList.h"
#include <QFileDialog>
#include <QtDebug>
#include <QWidget>
#include <sizedialog.h>
#include <globals.h> //V_GLOBAL.G_ROW and V_GLOBAL.G_COL
#include <FrameManipulation.h>

long FrameID = 0; //-P
QColor temp_RGB; //yeah.... -P
//FrameList frameList(V_GLOBAL.G_ROW,V_GLOBAL.G_COL);

GridSquare *Lcolor = new GridSquare(true);
GridSquare *Rcolor = new GridSquare(true);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gridScene = new QGraphicsScene(this);
    ui->gView_Grid->setScene(gridScene); //give the grid to the graphics view -Paul

    timelineScene = new QGraphicsScene(this);
    ui->gView_Timeline->setScene(timelineScene); //give the timeline to the graphics view -Paul

    currentcolorsScene = new QGraphicsScene(this);
    ui->gCurrent_Colors->setScene(currentcolorsScene);

    Lcolor->x = 0;
    Lcolor->y = 0;
    Rcolor->x = 0;
    Rcolor->y = 40;

    currentcolorsScene->addItem(Lcolor);
    currentcolorsScene->addItem(Rcolor);
    //GridSquare **square = new GridSquare*[V_GLOBAL.G_COL];  //This is now in mainwindow.h -P
    for (int i = 0; i < V_GLOBAL.G_ROW; ++i)
    {
        gridGridSquare[i] = new GridSquare[V_GLOBAL.G_COL];
        timelineTimelineGrid[i] = new TimelineGrid[V_GLOBAL.G_COL];
    }

    //MAIN WINDOW TOO BIG, gonna take the scaling down to 85% -P
    double max = 0;
    if(V_GLOBAL.G_ROW > V_GLOBAL.G_COL)
        max = V_GLOBAL.G_ROW;
    else
        max = V_GLOBAL.G_COL;
    double G_SCALE = ((20.0 / max) * 0.85); //scaled based on a max size of 20x20 -P

    int gridScale = 22*G_SCALE;
    int timelineScale = 4*G_SCALE;
    int g_SPACING = 3; //grid spacing woohooo -P
    int t_SPACING = 2; //timeline spacing woohooo -P

    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].y = (x*gridScale + x*g_SPACING);
            gridGridSquare[x][y].x = (y*gridScale + y*g_SPACING);
            timelineTimelineGrid[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
            timelineTimelineGrid[x][y].x = (y*timelineScale + y*t_SPACING); //will add the magic soon -P
            gridScene->addItem(&gridGridSquare[x][y]);
            timelineScene->addItem(&timelineTimelineGrid[x][y]); //timeline testing here -P
        }
    }

    ColorWheel *wheel = new ColorWheel;
    QSpinBox *spinbox = new QSpinBox;
    //connect(wheel, SIGNAL(colorChange(QColor)), spinbox, SLOT(on_sbox_ValueRed_editingFinished()));

    //Start the FrameData nonsense -P
    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // set grid size
    t_FrameData FrameData;  // THE frame data (this is in mainwindow.h) -P
    //FrameList frameList(V_GLOBAL.G_ROW, V_GLOBAL.G_COL); // linked list for frame data. r c for print function

    FrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);  // Generate new rgb_data arrary




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

    //FileOperations::SaveToFile(frameList,fileName);
    qDebug() << "Returned safely";
}

void MainWindow::on_actionOpenProject_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Project"), "",
            tr("Project (*.tan);;All Files (*)"));

    //FrameList frameList(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);
    //FileOperations::LoadFromFile(fileName, &frameList);
}


void MainWindow::on_sbox_ValueRed_editingFinished()
{
    //crap -P
    V_GLOBAL.G_LEFT.setRed( ui->sbox_ValueRed->value() ); //allow custom colors via the spinboxes -P
}

void MainWindow::on_sbox_ValueGreen_editingFinished()
{
    V_GLOBAL.G_LEFT.setGreen( ui->sbox_ValueGreen->value() ); //allow custom colors via the spinboxes -P
}

void MainWindow::on_sbox_ValueBlue_editingFinished()
{
    V_GLOBAL.G_LEFT.setBlue( ui->sbox_ValueBlue->value() ); //allow custom colors via the spinboxes -P
}


void MainWindow::mousePressEvent(QMouseEvent *event) //any time the window is clicked inside of, lol -P
{

    //Rcolor->square_RGB.setRgb(G_RED_RIGHT, G_GREEN_RIGHT, G_BLUE_RIGHT, 255);
    //Lcolor->square_RGB.setRgb(G_RED, G_GREEN, G_BLUE, 255);

    Rcolor->square_RGB.setRgb(V_GLOBAL.G_RIGHT.red(), V_GLOBAL.G_RIGHT.green(), V_GLOBAL.G_RIGHT.blue(), 255); //new -P
    Lcolor->square_RGB.setRgb(V_GLOBAL.G_LEFT.red(), V_GLOBAL.G_LEFT.green(), V_GLOBAL.G_LEFT.blue(), 255); //new -P

    Rcolor->update();
    Lcolor->update();
    
    //gridToFrameData(); //on every click lol -P
    updateTimeline(); //lol -P
}


void MainWindow::on_btn_FillFrame_clicked() //Fill Frame
{
    //first let's update the GRAPHICAL EYBALL STIMILATION GRID for motivation -P
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
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
    V_GLOBAL.G_LEFT = temp_RGB;

    ui->sbox_ValueRed->setValue(V_GLOBAL.G_LEFT.red()); //-P
    ui->sbox_ValueGreen->setValue(V_GLOBAL.G_LEFT.green());
    ui->sbox_ValueBlue->setValue(V_GLOBAL.G_LEFT.blue()); //-P
}

void MainWindow::on_btn_ClearFrame_pressed() //Clear Frame
{
    temp_RGB = V_GLOBAL.G_LEFT;
    //first let's update the GRAPHICAL EYBALL STIMILATION GRID for motivation -P
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].Selected = true;
            gridGridSquare[x][y].leftclick = true;
            //BLACK
            //G_RED = 0;
            //G_GREEN = 0;
            //G_BLUE = 0;
            V_GLOBAL.G_LEFT = (Qt::black); //new -P
            gridGridSquare[x][y].update(); //Fill that frame son -P
        }
    }

    //do this:

    //fillFrame2(FrameData, 0, 0, 0); //not tested yet -P
}

void MainWindow::updateTimeline() //fix the update lag later -P
{
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            timelineTimelineGrid[x][y].square_RGB = gridGridSquare[x][y].square_RGB; //grab the colors from the real grid -P
            timelineTimelineGrid[x][y].update();
        }
    }
}

