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

FrameList theFrames(V_GLOBAL.G_ROW, V_GLOBAL.G_COL); //HERE LAY THE LINKED LIST -P

int CurrentFrameNum = 0;

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

    //MAIN WINDOW TOO BIG, gonna take the scaling down to 85% -P
    max = 0;
    if(V_GLOBAL.G_ROW > V_GLOBAL.G_COL)
        max = V_GLOBAL.G_ROW;
    else
        max = V_GLOBAL.G_COL;
    G_SCALE = ((20.0 / max) * 0.85); //scaled based on a max size of 20x20 -P

    gridScale = 22*G_SCALE;
    timelineScale = 4*G_SCALE;
    g_SPACING = 3; //grid spacing woohooo -P
    t_SPACING = 2; //timeline spacing woohooo -P


    Lcolor->x = 0;
    Lcolor->y = 0;
    Rcolor->x = 0;
    Rcolor->y = 40;

    theFrames.SetRowCount(V_GLOBAL.G_ROW);        // Update row size in FrameList now that it is defined
    theFrames.SetColCount(V_GLOBAL.G_COL);        // Update col size in FrameList now that it is defined

    // Setup very first frame to start with
    // This 'fristFrameData' might be combined with currentFrameData
    t_FrameData firstFrameData;
    firstFrameData.ID = FrameID++;
    firstFrameData.duration = 5;                  // arbritrary. Link to initial durration in gui
    firstFrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);
    theFrames.AddTail(firstFrameData);            // Put first frame onto the FrameList

    CurrentFrameData = theFrames.FirstNode();     // Get initial frame from the FrameList

    //t_FrameData * testptr = theFrames.RetrieveNode_Middle(0); //This is the correct formate -n

    currentcolorsScene->addItem(Lcolor);
    currentcolorsScene->addItem(Rcolor);
    //GridSquare **square = new GridSquare*[V_GLOBAL.G_COL];  //This is now in mainwindow.h -P
    gridGridSquare = new GridSquare*[V_GLOBAL.G_ROW];
    for (int i = 0; i < V_GLOBAL.G_ROW; ++i)
    {
        gridGridSquare[i] = new GridSquare[V_GLOBAL.G_COL];

        tempSquareData[i] = new TimelineGrid[V_GLOBAL.G_COL]; //old -P
        tempSquareData2[i] = new TimelineGrid[V_GLOBAL.G_COL]; //old -P
        CurrentFrameData.squareData[i] = new TimelineGrid[V_GLOBAL.G_COL]; //new $$$$$4 -P
        //FrameData.squareData[i] = new TimelineGrid[V_GLOBAL.G_COL]; //move this? -P
        //FrameData2.squareData[i] = new TimelineGrid[V_GLOBAL.G_COL]; //-P
    }

    //CurrentFrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);
    //FrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);
    //FrameData2.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);



    //draw the grid -P
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].y = (x*gridScale + x*g_SPACING);
            gridGridSquare[x][y].x = (y*gridScale + y*g_SPACING);
            gridScene->addItem(&gridGridSquare[x][y]);
        }
    }

} //end mainwindow

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
    // Set square to color
    Rcolor->square_RGB = V_GLOBAL.G_RIGHT;
    Lcolor->square_RGB = V_GLOBAL.G_LEFT;

    // Update GUI
    Rcolor->update();
    Lcolor->update();

    theFrames.PrintNode(); //DEBUG IT -P


    //set grid to current frame -P
    if(V_GLOBAL.G_TIMELINESELECTED == true)
    {
        tempSquareData2 = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME)->squareData; //grab the current frame -P
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                gridGridSquare[x][y].square_RGB = tempSquareData2[x][y].square_RGB; //give the data to the grid -P
                gridGridSquare[x][y].update(); //Fill that frame son -P
            }
        }
    }


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
    updateTimeline();
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
            V_GLOBAL.G_LEFT = (Qt::black);  // set color to black -n
            gridGridSquare[x][y].update();  //Fill that frame son -P
        }
    }

    //do this:

    //fillFrame2(FrameData, 0, 0, 0); //not tested yet -P
    updateTimeline();
}

void MainWindow::updateTimeline() //fix the update lag later -P
{
    {
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                (theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME)->squareData)[x][y].square_RGB = gridGridSquare[x][y].square_RGB;
                (theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME)->squareData)[x][y].update();
            }
        }
    }
}


void MainWindow::on_btn_NewFrame_clicked()
{
    V_GLOBAL.G_FRAMECOUNT++; //add a frame to the count
    FrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL, V_GLOBAL.G_FRAMECOUNT); //fix indexing later -P
    //FrameData.squareData[i % V_GLOBAL.G_ROW][i % V_GLOBAL.G_COL].square_RGB = (Qt::blue); //show that each frame is in fact unique
    theFrames.AddTail(FrameData);

    //Draw the timeline! -P
    for(int i=0; i < V_GLOBAL.G_FRAMECOUNT; i++)
    {
        //tempSquareData = theFrames.RetrieveNode_Middle(i)->squareData;
        tempSquareData = FrameData.squareData;
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                tempSquareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
                tempSquareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P

                timelineScene->addItem(&(tempSquareData[x][y])); //timeline painting here -P
            }
        }
    }
    V_GLOBAL.G_CURRENTFRAME = V_GLOBAL.G_FRAMECOUNT; //fix indexing later -P

    //this sets the current frame you are editing to the new frame: -P
    {
        tempSquareData2 = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME)->squareData; //grab the current frame -P
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                gridGridSquare[x][y].square_RGB = tempSquareData2[x][y].square_RGB; //give the data to the grid -P
                gridGridSquare[x][y].update(); //Fill that frame son -P
            }
        }
    }
}

void MainWindow::on_btn_DeleteFrame_clicked()
{
    if(V_GLOBAL.G_FRAMECOUNT != 0) //can't delete once there are no frames
    {
        if(V_GLOBAL.G_CURRENTFRAME == (V_GLOBAL.G_FRAMECOUNT)) // the last frame is being deleted -P
        {
            theFrames.DeleteNode_Middle(V_GLOBAL.G_CURRENTFRAME); //simple
            updateTimeline();
        }
        else //Deleting a frame in the middle of the timeline, bugger -P
        {
            theFrames.DeleteNode_Middle(V_GLOBAL.G_CURRENTFRAME);
            for(int i=V_GLOBAL.G_CURRENTFRAME; i<V_GLOBAL.G_FRAMECOUNT; i++) //go through all remaing frames after the deletion -P
            {
                for(int x=0; x<V_GLOBAL.G_ROW; x++)
                {
                    for(int y=0; y<V_GLOBAL.G_COL; y++)
                    {
                        theFrames.RetrieveNode_Middle(i)->squareData[x][y].timlineFrameNumber--; //decrement frame number by 1
                    }
                }
            }
            updateTimeline(); //redraw -P
        }
        V_GLOBAL.G_FRAMECOUNT--; //remove 1 from the framecount -P
    }
}
