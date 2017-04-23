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
#include <player.h>
#include <QApplication> //OP weapon -P
#include <docdialog.h>
#include <helpdialog.h>

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


    //V_GLOBAL.G_FRAMELIST->SetColCount(V_GLOBAL.G_COL);
    //V_GLOBAL.G_FRAMELIST->SetRowCount(V_GLOBAL.G_ROW);
    V_GLOBAL.G_FRAMELIST = &theFrames;


    CurrentFrameData = theFrames.FirstNode();     // Get initial frame from the FrameList

    //t_FrameData * testptr = theFrames.RetrieveNode_Middle(0); //This is the correct formate -n

    currentcolorsScene->addItem(Lcolor);
    currentcolorsScene->addItem(Rcolor);

    // This generates the memory for these grids
    gridGridSquare = new GridSquare*[V_GLOBAL.G_ROW];
    for (int i = 0; i < V_GLOBAL.G_ROW; ++i)
    {
        gridGridSquare[i] = new GridSquare[V_GLOBAL.G_COL];
    }

    // is this needed? Is it needed if we dont use a first frame above? -n
    //CurrentFrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);

    drawGrid();
    on_btn_NewFrame_clicked(); //pseudo-fix for first frame not showing on timeline, fix the bug

} //end mainwindow

MainWindow::~MainWindow()
{
    for (int i = 0; i < V_GLOBAL.G_ROW; ++i)
    {
        delete [] gridGridSquare[i];
    }

    delete ui;
    exit(0); //WHOA fixed the SIGABRT on Linux -P
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Project"), "",
            tr("Project (*.tan);;All Files (*)"));

    FileOperations::SaveToFile(fileName,theFrames);
    qDebug() << "Returned safely";
}

void MainWindow::on_actionOpenProject_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Project"), "",
            tr("Project (*.tan);;All Files (*)"));

    if(FileOperations::LoadFromFile(fileName, &theFrames) == -1){
        std::cout << "Failed to open" << std::endl;
    }

    theFrames.PrintNode();

    V_GLOBAL.G_CURRENTFRAME = theFrames.Size() - 1;
    V_GLOBAL.G_FRAMECOUNT = theFrames.Size();
    V_GLOBAL.G_COL = theFrames.GetColCount();
    V_GLOBAL.G_ROW = theFrames.GetRowCount();
    updateTimeline();
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
        t_FrameData *tempFrameData = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the current frame
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                gridGridSquare[x][y].square_RGB = (*tempFrameData).squareData[x][y].square_RGB; //give the data to the grid -P
                gridGridSquare[x][y].update(); //Fill that frame son -P
            }
        }
        //show duration of current frame
        ui->dsbox_FrameDur->setValue((*tempFrameData).duration);

        //draw red square around frame -P

        QPen redPen;
        QPen clearPen;
        QColor clear;
        clear.setRgb(211,215,207,255);
        redPen.setColor(Qt::blue); //lol, not even red anymore -P
        redPen.setWidth(4);
        clearPen.setColor(clear);
        clearPen.setWidth(4);

        //int redSpacingX = V_GLOBAL.G_COL*timelineScale + V_GLOBAL.G_COL*t_SPACING + 30;
        int redSpacingX = 110;
        int redSizeX = V_GLOBAL.G_COL*timelineScale + V_GLOBAL.G_COL*t_SPACING + 20;
        int redSizeY = V_GLOBAL.G_ROW*timelineScale + V_GLOBAL.G_ROW*t_SPACING + 20;

        //timelineScene->clear();
        for(int i=0;i<V_GLOBAL.G_FRAMECOUNT;i++)
        {
            timelineScene->addRect((((i)*redSpacingX)-10),(-10),redSizeX,redSizeY,clearPen,(Qt::NoBrush));
        }

        timelineScene->addRect((((V_GLOBAL.G_CURRENTFRAME-1)*redSpacingX)-10),(-10),redSizeX,redSizeY,redPen,(Qt::NoBrush));
        drawTimeline();
        //P
    }

    qApp->processEvents(); //Extremely OP weapon, fixes all lag, use with caution -P

    updateTimeline(); //lol -P
}


void MainWindow::on_btn_FillFrame_clicked() //Fill Frame
{
    t_FrameData *currentFrameFill = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);

    fillFrame(currentFrameFill, Lcolor->square_RGB); //do this later -P

    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = currentFrameFill->squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
    updateTimeline();
}

void MainWindow::on_btn_ClearFrame_clicked() //Clear Frame
{
    t_FrameData *currentFrameFill = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);

    fillFrame(currentFrameFill, Qt::black);

    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = currentFrameFill->squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
    updateTimeline();
}

void MainWindow::drawGrid()
{
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
}

void MainWindow::updateTimeline() //fix the update lag later -P
{
    t_FrameData *tempFrameData = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the current frame
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            (*tempFrameData).squareData[x][y].square_RGB = gridGridSquare[x][y].square_RGB;
            (*tempFrameData).squareData[x][y].update();
        }
    }
}


void MainWindow::on_btn_NewFrame_clicked()
{
    V_GLOBAL.G_FRAMECOUNT++; //add a frame to the count
    FrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL, V_GLOBAL.G_FRAMECOUNT); //fix indexing later -P
    //FrameData.squareData[i % V_GLOBAL.G_ROW][i % V_GLOBAL.G_COL].square_RGB = (Qt::blue); //show that each frame is in fact unique
    theFrames.AddTail(FrameData);

    V_GLOBAL.G_CURRENTFRAME = V_GLOBAL.G_FRAMECOUNT; //fix indexing later -P

    //draw red square around frame -P

    QPen redPen;
    QPen clearPen;
    QColor clear;
    clear.setRgb(211,215,207,255);
    redPen.setColor(Qt::blue);
    redPen.setWidth(4);
    clearPen.setColor(clear);
    clearPen.setWidth(4);

    //int redSpacingX = V_GLOBAL.G_COL*timelineScale + V_GLOBAL.G_COL*t_SPACING + 30;
    int redSpacingX = 110;
    int redSizeX = V_GLOBAL.G_COL*timelineScale + V_GLOBAL.G_COL*t_SPACING + 20;
    int redSizeY = V_GLOBAL.G_ROW*timelineScale + V_GLOBAL.G_ROW*t_SPACING + 20;

    //timelineScene->clear();
    for(int i=0;i<V_GLOBAL.G_FRAMECOUNT;i++)
    {
        timelineScene->addRect((((i)*redSpacingX)-10),(-10),redSizeX,redSizeY,clearPen,(Qt::NoBrush));
    }

    timelineScene->addRect((((V_GLOBAL.G_CURRENTFRAME-1)*redSpacingX)-10),(-10),redSizeX,redSizeY,redPen,(Qt::NoBrush));
    drawTimeline();
    //P

    //this sets the current frame you are editing to the new frame: -P

    t_FrameData *tempFrameData = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the current frame
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData).squareData[x][y].square_RGB; //give the data to the grid -P
            gridGridSquare[x][y].update(); //Fill that frame son -P
        }
    }

    //show duration of new frame
    ui->dsbox_FrameDur->setValue((*tempFrameData).duration);
}

void MainWindow::on_btn_DeleteFrame_clicked()
{
    if(V_GLOBAL.G_FRAMECOUNT != 0) //can't delete once there are no frames
    {
        if(V_GLOBAL.G_CURRENTFRAME == (V_GLOBAL.G_FRAMECOUNT-1)) // the last frame is being deleted -P
        {
            theFrames.DeleteNode_Middle(V_GLOBAL.G_CURRENTFRAME); //simple
            updateTimeline();
        }
        else //Deleting a frame in the middle of the timeline, bugger -P
        {
            theFrames.DeleteNode_Middle(V_GLOBAL.G_CURRENTFRAME);
            for(int i=V_GLOBAL.G_CURRENTFRAME+1; i<V_GLOBAL.G_FRAMECOUNT; i++) //go through all remaing frames after the deletion -P
            {
                t_FrameData *tempFrameData = theFrames.RetrieveNode_Middle(i);   //grab the this frame
                for(int x=0; x<V_GLOBAL.G_ROW; x++)
                {
                    for(int y=0; y<V_GLOBAL.G_COL; y++)
                    {
                        (*tempFrameData).squareData[x][y].timelineFrameNumber--; //decrement frame number by 1
                    }
                }
            }
            updateTimeline(); //redraw -P
            //crap
        }
        V_GLOBAL.G_FRAMECOUNT--; //remove 1 from the framecount -P
    }
    //Redraw the timeline! -P
    for(int i=V_GLOBAL.G_CURRENTFRAME-1; i < V_GLOBAL.G_FRAMECOUNT; i++) //start from current frame, avoid lag -P
    {
        t_FrameData *tempFrameData = theFrames.RetrieveNode_Middle(i);   //grab the this frame
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                (*tempFrameData).squareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
                (*tempFrameData).squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P

                timelineScene->addItem(&((*tempFrameData).squareData[x][y])); //timeline painting here -P
            }
        }
    }
}

void MainWindow::insertFrame(t_FrameData newFrame)
{
    //do this later lol
}

void MainWindow::on_dsbox_FrameDur_valueChanged(double arg1)
{
    if (V_GLOBAL.G_CURRENTFRAME > 0)
        theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME)->duration = arg1;
}

void MainWindow::on_btn_TransUP_clicked()
{
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);  //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    // Get current new Frame
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);       //grab the current frame

    // Copy prev Frame Into current new frame. Arguments have to be pointers
    copyFrame(tempFrameData_current, tempFrameData_prev);

    // Translate newframe by direction

    translateFrame(tempFrameData_current, D_UP);

    // copy current frame into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::on_btn_TransRight_clicked()
{
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);  //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    // Get current new Frame
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);       //grab the current frame

    // Copy prev Frame Into current new frame. Arguments have to be pointers
    copyFrame(tempFrameData_current, tempFrameData_prev);

    // Translate newframe by direction

    translateFrame(tempFrameData_current, D_RIGHT);

    // copy current frame into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::on_btn_TransLeft_clicked()
{
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);  //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    // Get current new Frame
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);       //grab the current frame

    // Copy prev Frame Into current new frame. Arguments have to be pointers
    copyFrame(tempFrameData_current, tempFrameData_prev);

    // Translate newframe by direction

    translateFrame(tempFrameData_current, D_LEFT);

    // copy current frame into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::on_btn_TransDwn_clicked()
{
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);  //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    // Get current new Frame
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);       //grab the current frame

    // Copy prev Frame Into current new frame. Arguments have to be pointers
    copyFrame(tempFrameData_current, tempFrameData_prev);

    // Translate newframe by direction

    translateFrame(tempFrameData_current, D_DWN);

    // copy current frame into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::on_btn_TransDwnRight_clicked()
{
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);  //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    // Get current new Frame
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);       //grab the current frame

    // Copy prev Frame Into current new frame. Arguments have to be pointers
    copyFrame(tempFrameData_current, tempFrameData_prev);

    // Translate newframe by direction

    translateFrame(tempFrameData_current, D_DWN_R);

    // copy current frame into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::on_btn_TransDwnLeft_clicked()
{
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);  //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    // Get current new Frame
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);       //grab the current frame

    // Copy prev Frame Into current new frame. Arguments have to be pointers
    copyFrame(tempFrameData_current, tempFrameData_prev);

    // Translate newframe by direction

    translateFrame(tempFrameData_current, D_DWN_L);

    // copy current frame into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::on_btn_TransUpLeft_clicked()
{
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);  //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    // Get current new Frame
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);       //grab the current frame

    // Copy prev Frame Into current new frame. Arguments have to be pointers
    copyFrame(tempFrameData_current, tempFrameData_prev);

    // Translate newframe by direction

    translateFrame(tempFrameData_current, D_UP_L);

    // copy current frame into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::on_btn_TransUpRight_clicked()
{
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);  //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    // Get current new Frame
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);       //grab the current frame

    // Copy prev Frame Into current new frame. Arguments have to be pointers
    copyFrame(tempFrameData_current, tempFrameData_prev);

    // Translate newframe by direction

    translateFrame(tempFrameData_current, D_UP_R);

    // copy current frame into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::on_btn_RepeatFrame_clicked()
{
    on_btn_NewFrame_clicked();
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the current frame
    t_FrameData *tempFrameData_prev    = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME-1); //grab the previous frame
    t_FrameData newFrameData;                                                // New frame
    newFrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);    // Allocate new frame

// Change implementation to this. First need to update copyFrame to use pointers to t_FrameData
//ref    int copyFrame(t_FrameData &copyFrame, t_FrameData origFrame);
    //copyFrame(transFrameData, tempFrameData_current);


    // copy prev frame into transFrameData
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            newFrameData.squareData[x][y].square_RGB = (*tempFrameData_prev).squareData[x][y].square_RGB;
        }
    }
    // copy transFrameData into current frame
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            (*tempFrameData_current).squareData[x][y].square_RGB = newFrameData.squareData[x][y].square_RGB;
        }
    }
    // copy transFrameData into gridGridSquare
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].square_RGB = (*tempFrameData_current).squareData[x][y].square_RGB;
            gridGridSquare[x][y].update();
        }
    }
}

void MainWindow::drawTimeline()
{
    for(int i=V_GLOBAL.G_CURRENTFRAME-1; i < V_GLOBAL.G_FRAMECOUNT; i++) //start at current frame to avoid the lag -P
    {
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                FrameData.squareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
                FrameData.squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P

                timelineScene->addItem(&(FrameData.squareData[x][y])); //timeline painting here -P
            }
        }
    }
}

void MainWindow::on_btn_PlayPause_clicked()
{
    Player dialog2;
    dialog2.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint); //You will NOT exit this window your way -P
    dialog2.setModal(true); //YOU SHALL NOT CLICK OUTSIDE OF THIS WINDOW -P
    dialog2.exec(); //execute pls -P
}

void MainWindow::on_actionAbout_triggered()
{
    //pop the help dialog -P
    helpdialog dialog2;
    dialog2.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint); //You will NOT exit this window your way -P
    dialog2.setModal(true); //YOU SHALL NOT CLICK OUTSIDE OF THIS WINDOW -P
    dialog2.exec(); //execute pls -P
}

void MainWindow::on_actionDocumentation_triggered()
{
    //pop the doc dialog -P
    docdialog dialog2;
    dialog2.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint); //You will NOT exit this window your way -P
    dialog2.setModal(true); //YOU SHALL NOT CLICK OUTSIDE OF THIS WINDOW -P
    dialog2.exec(); //execute pls -P
}

void MainWindow::on_actionPlay_All_triggered()
{
    on_btn_PlayPause_clicked();
}
