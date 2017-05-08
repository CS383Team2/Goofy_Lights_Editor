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
#include "gridsquarewrapper.h"

int FrameID = 0; //-P
QColor temp_RGB; //yeah.... -P

FrameList theFrames(V_GLOBAL.G_ROW, V_GLOBAL.G_COL); //HERE LAY THE LINKED LIST -P

int CurrentFrameNum = 0;

PaletteSquare *Lcolor = new PaletteSquare(0,0,Qt::red);
PaletteSquare *Rcolor = new PaletteSquare(0,32.5,Qt::blue);

Palette *currentPalette = new Palette;

gridsquarewrapper mainGrid;

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

    paletteScene = new QGraphicsScene(this);
    ui->gPalette->setScene(paletteScene);

    //MAIN WINDOW TOO BIG, gonna take the scaling down to 85% -P
    max_size = 0;
    if(V_GLOBAL.G_ROW > V_GLOBAL.G_COL)
        max_size = V_GLOBAL.G_ROW;
    else
        max_size = V_GLOBAL.G_COL;
    G_SCALE = ((20.0 / max_size) * 0.85); //scaled based on a max size of 20x20 -P

    timelineScale = 4*G_SCALE;
    t_SPACING = 2; //timeline spacing woohooo -P

    theFrames.SetRowCount(V_GLOBAL.G_ROW);        // Update row size in FrameList now that it is defined
    theFrames.SetColCount(V_GLOBAL.G_COL);        // Update col size in FrameList now that it is defined
    // V_GLOBAL.G_FRAMELIST = &theFrames;            // Attach FrameList to Global structure

    /* Global filename is only set in loading */
    if(V_GLOBAL.G_FILENAME != NULL){
        theFrames.DeleteList();
        theFrames.SetColCount(V_GLOBAL.G_FRAMELIST->GetColCount());
        theFrames.SetRowCount(V_GLOBAL.G_FRAMELIST->GetRowCount());

        int i;
        for(i = 0; i < V_GLOBAL.G_FRAMECOUNT; i++){
            t_FrameData tempFrameData;
            tempFrameData = (*(V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(i)));
            theFrames.AddTail(tempFrameData);
        }
        initializeEntireTimeline();
    }

    V_GLOBAL.G_FRAMELIST = &theFrames;

    V_GLOBAL.G_CURRENTFRAME = theFrames.Size();

    //t_FrameData * testptr = theFrames.RetrieveNode_Middle(0); //This is the correct formate -n

    currentcolorsScene->addItem(Lcolor);
    currentcolorsScene->addItem(Rcolor);

    mainGrid.generate();  // Generate memory space
    mainGrid.setScene(gridScene);
    mainGrid.drawGrid();
    
    // initializeEntireTimeline();
    if (V_GLOBAL.G_FRAMECOUNT == 0) createFirstFrame(); //pseudo-fix for first frame not showing on timeline, fix the bug

    currentPalette->insertColor(V_GLOBAL.G_LEFT);
    currentPalette->insertColor(V_GLOBAL.G_RIGHT);

    drawPalette();

    //here are some tooltips, perhaps make a function to toggle them on/off:
    ui->btn_NewFrame->setToolTip("Adds a new frame right after this current frame."); //fancy tool tips for detail -P
    ui->btn_DeleteFrame->setToolTip("Deletes the currently selected frame.");
    ui->btn_CopyFrame->setToolTip("Copies the currently selected frame to the clipboard.");
    ui->btn_ClearFrame->setToolTip("Clears every square in the current frame.");
    ui->btn_FillFrame->setToolTip("Fills every square in the current frame with the currently celected color.");
    ui->btn_PasteFrame->setToolTip("Pastes the frame from the clipboard into the currently selected frame.");
    ui->btn_PlayPause->setToolTip("Plays the entire animation from start to finish"); //fix this later -P
    ui->btn_RepeatFrame->setToolTip("Make a copy of this frame and insert it as the next frame.");

} //end mainwindow

MainWindow::~MainWindow()
{
    delete ui;
    exit(0); //WHOA fixed the SIGABRT on Linux -P
}

void MainWindow::on_actionSave_As_triggered()
{
    /*
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Project"), "",
            tr("Project (*.tan);;All Files (*)"));
            */

    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                    "Save some file", QString(),
                                                    tr("Tan files (*.tan);; All Files (*)"), nullptr,
                                                    QFileDialog::ReadOnly | QFileDialog::DontUseNativeDialog);

    if(fileName == NULL)
        return;

    FileOperations::SaveToFile(fileName,&theFrames);
    qDebug() << "Returned safely";
}

void MainWindow::on_actionOpenProject_triggered()
{
    /*
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Project"), "",
            tr("Project (*.tan);;All Files (*)"));
            */
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    "Open some file", QString(),
                                                    tr("Tan files (*.tan);; All Files (*)"), nullptr,
                                                    QFileDialog::ReadOnly | QFileDialog::DontUseNativeDialog);

    if(fileName == NULL)
        return;

    theFrames.DeleteList();

    if(FileOperations::LoadFromFile(fileName, &theFrames) == -1){
        std::cout << "Failed to open" << std::endl;
    }

    V_GLOBAL.G_CURRENTFRAME = theFrames.Size() - 1;
    V_GLOBAL.G_FRAMECOUNT = theFrames.Size();
    V_GLOBAL.G_COL = theFrames.GetColCount();
    V_GLOBAL.G_ROW = theFrames.GetRowCount();

    if(V_GLOBAL.G_ROW > V_GLOBAL.G_COL)
        max_size = V_GLOBAL.G_ROW;
    else
        max_size = V_GLOBAL.G_COL;
    G_SCALE = ((20.0 / max_size) * 0.85); //scaled based on a max size of 20x20 -P

    timelineScale = 4*G_SCALE;

    mainGrid.clearGrid();
    mainGrid.generate();  // Generate memory space
    mainGrid.setScene(gridScene);
    mainGrid.drawGrid();

    initializeEntireTimeline();
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

    if (event->button() == Qt::RightButton)
        currentPalette->insertColor(V_GLOBAL.G_RIGHT);
    else
        currentPalette->insertColor(V_GLOBAL.G_LEFT);

    drawPalette();

    setCursor(Qt::ArrowCursor);

    //set grid to current frame -P
    if(V_GLOBAL.G_TIMELINESELECTED == true)
    {
        t_FrameData *tempFrameData = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the current frame
        mainGrid.loadFrame(tempFrameData); // copy frame into editing grid
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

        timelineScene->addRect((((V_GLOBAL.G_CURRENTFRAME)*redSpacingX)-10),(-10),redSizeX,redSizeY,redPen,(Qt::NoBrush));
    }


    qApp->processEvents(); //Extremely OP weapon, fixes all lag, use with caution -P

    updateTimeline(); //lol -P
}

void MainWindow::on_btn_FillFrame_clicked() //Fill Frame
{
    t_FrameData *currentFrameFill = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);

    fillFrame(currentFrameFill, Lcolor->square_RGB); //do this later -P

    mainGrid.loadFrame(currentFrameFill); // copy frame into editing grid
    updateTimeline();

    newGridColor = true;
    currentPalette->insertColor(V_GLOBAL.G_LEFT);
    drawPalette();

}

void MainWindow::on_btn_ClearFrame_clicked() //Clear Frame
{
    t_FrameData *currentFrameFill = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);

    fillFrame(currentFrameFill, Qt::black);

    mainGrid.loadFrame(currentFrameFill); // copy frame into editing grid
    updateTimeline();
}

void MainWindow::updateTimeline() //fix the update lag later -P
{
    t_FrameData *tempFrameData = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the current frame
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            (*tempFrameData).squareData[x][y].square_RGB = mainGrid.gridSquareData[x][y].square_RGB;
            (*tempFrameData).squareData[x][y].update();
        }
    }

    ui->dsbox_FrameDur->setValue((*tempFrameData).duration);

    double currtime = 0.0;
    for (int i = 0; i < V_GLOBAL.G_CURRENTFRAME; i++) //This is broken
        currtime += theFrames.RetrieveNode_Middle(i)->duration;
    ui->dsbox_CurrTime->setValue(currtime);
}

void MainWindow::createFirstFrame()
{
    FrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL, 0); //fix indexing later -P
    theFrames.AddTail(FrameData);
    V_GLOBAL.G_FRAMECOUNT++;
    newFrameHandler();
}

void MainWindow::on_btn_NewFrame_clicked()
{
    V_GLOBAL.G_CURRENTFRAME++;
    FrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL, V_GLOBAL.G_CURRENTFRAME);
    theFrames.AddNode_Middle(FrameData, V_GLOBAL.G_CURRENTFRAME);
    V_GLOBAL.G_FRAMECOUNT++; //add a frame to the count
    if(translateClicked == false)
        newFrameHandler();
}


void MainWindow::on_btn_DeleteFrame_clicked()
{
    t_FrameData *tempFrameData = theFrames.RetrieveNode_Middle(V_GLOBAL.G_FRAMECOUNT-1);

    if (V_GLOBAL.G_FRAMECOUNT == 1)
    {
        on_btn_ClearFrame_clicked();
        return;
    }
    else
    {
        for (int i = 0; i < V_GLOBAL.G_ROW; i++)
            for (int j = 0; j < V_GLOBAL.G_COL; j++)
                timelineScene->removeItem(&(tempFrameData->squareData[i][j]));
        for (int i = V_GLOBAL.G_CURRENTFRAME; i < V_GLOBAL.G_FRAMECOUNT-1; i++)
        {
            t_FrameData *prevFrameData = theFrames.RetrieveNode_Middle(i);
            t_FrameData *nextFrameData = theFrames.RetrieveNode_Middle(i+1);

            for (int i = 0; i < V_GLOBAL.G_ROW; i++)
                for (int j = 0; j < V_GLOBAL.G_COL; j++)
                    prevFrameData->squareData[i][j].square_RGB = nextFrameData->squareData[i][j].square_RGB;
            prevFrameData->duration = nextFrameData->duration;
            prevFrameData->ID = nextFrameData->ID;
        }

        // If last frame subtract current frame
        if (V_GLOBAL.G_CURRENTFRAME == V_GLOBAL.G_FRAMECOUNT-1)
            V_GLOBAL.G_CURRENTFRAME--;
        mainGrid.loadFrame(theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME));
        V_GLOBAL.G_TIMELINESELECTED = true;

        QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, QCursor::pos(), Qt::MouseButton::LeftButton, NULL, NULL);

        mousePressEvent(event);

        theFrames.DeleteNode_Middle(V_GLOBAL.G_FRAMECOUNT-1);
        V_GLOBAL.G_FRAMECOUNT = V_GLOBAL.G_FRAMECOUNT - 1;
    }
}

void MainWindow::insertFrame(t_FrameData newFrame)
{
    //do this later lol
}

void MainWindow::on_dsbox_FrameDur_valueChanged(double arg1)
{
    if (V_GLOBAL.G_CURRENTFRAME >= 0)
        theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME)->duration = arg1;
}

void MainWindow::ProcessTranslateFrame(int DIR)
{
    translateClicked = true;
    // Get previous Frame for the purpose of copying later
    t_FrameData *tempFrameData_prev = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the previous frame

    // on_btn_NewFrame creates new node & adds to framelist. Then updates G_CURRENTFRAME to new frame
    on_btn_NewFrame_clicked();

    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME); // Get current new Frame

    copyFrame(tempFrameData_current, tempFrameData_prev);                    // Copy prev Frame Into current new frame.
    translateFrame(tempFrameData_current, DIR); // Translate newframe by direction
    FrameData.squareData = tempFrameData_current->squareData;
    newFrameHandler();
    translateClicked = false;
}

void MainWindow::on_btn_TransUP_clicked()
{
    MainWindow::ProcessTranslateFrame(D_UP);
}

void MainWindow::on_btn_TransRight_clicked()
{
    MainWindow::ProcessTranslateFrame(D_RIGHT);
}

void MainWindow::on_btn_TransLeft_clicked()
{
    MainWindow::ProcessTranslateFrame(D_LEFT);
}

void MainWindow::on_btn_TransDwn_clicked()
{
    MainWindow::ProcessTranslateFrame(D_DWN);
}

void MainWindow::on_btn_TransDwnRight_clicked()
{
    MainWindow::ProcessTranslateFrame(D_DWN_R);
}

void MainWindow::on_btn_TransDwnLeft_clicked()
{
    MainWindow::ProcessTranslateFrame(D_DWN_L);
}

void MainWindow::on_btn_TransUpLeft_clicked()
{
    MainWindow::ProcessTranslateFrame(D_UP_L);
}

void MainWindow::on_btn_TransUpRight_clicked()
{
    MainWindow::ProcessTranslateFrame(D_UP_R);
}

void MainWindow::on_btn_RepeatFrame_clicked()
{
    on_btn_CopyFrame_clicked();
    on_btn_PasteFrame_clicked();
}

//BIG draw/refresh/all-in-one function. Handles adding drawing frame, refreshing timeline, drawing to grid, etc. Taken from onbtn_newFrame function.
void MainWindow::newFrameHandler()
{
    drawFrame();
    if(V_GLOBAL.G_CURRENTFRAME < V_GLOBAL.G_FRAMECOUNT-1)//Only refresh the list if the current frame being added is in the middle
        refreshTimelineAdd();

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
    timelineScene->addRect((((V_GLOBAL.G_CURRENTFRAME)*redSpacingX)-10),(-10),redSizeX,redSizeY,redPen,(Qt::NoBrush));

    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);
    mainGrid.loadFrame(tempFrameData_current); // copy frame into editing grid

    //show duration of new frame
    ui->dsbox_FrameDur->setValue((*tempFrameData_current).duration);

    //Scroll -P
    qApp->processEvents();
    qDebug() << "Current frame: " << V_GLOBAL.G_CURRENTFRAME << "Framecount: " << V_GLOBAL.G_FRAMECOUNT << endl;
    if((V_GLOBAL.G_CURRENTFRAME+1) == V_GLOBAL.G_FRAMECOUNT)
    ui->gView_Timeline->horizontalScrollBar()->setValue(( ui->gView_Timeline->horizontalScrollBar()->maximum()));
    //Keep timeline scrolled all the way to the RIGHT -P
}

//Draws and adds new frame to timeline
void MainWindow::drawFrame()
{
    int i = V_GLOBAL.G_CURRENTFRAME;
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

//Refreshes entire timeline
void MainWindow::initializeEntireTimeline()
{
    timelineScene = NULL;
    delete timelineScene;

    timelineScene = new QGraphicsScene(this);
    ui->gView_Timeline->setScene(timelineScene); //give the timeline to the graphics view -Paul

    timelineScene->update();

    for(int i=0; i < V_GLOBAL.G_FRAMECOUNT; i++) //loop through ALL? the frames -P
    {
        FrameData.squareData = theFrames.RetrieveNode_Middle(i)->squareData; //grab every frame
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                FrameData.squareData[x][y].timelineFrameNumber = i;
                FrameData.squareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
                FrameData.squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P
                timelineScene->addItem(&(FrameData.squareData[x][y])); //timeline painting here -P
            }
        }
    }
}

//Function that goes through the timeline and updates/moves frames after a frame is added in the middle of the list
void MainWindow::refreshTimelineAdd()
{
    for(int i= V_GLOBAL.G_CURRENTFRAME+1; i < V_GLOBAL.G_FRAMECOUNT; i++)
        {
            FrameData.squareData = theFrames.RetrieveNode_Middle(i)->squareData; //grabe every frame
            for(int x=0; x<V_GLOBAL.G_ROW; x++)
            {
                for(int y=0; y<V_GLOBAL.G_COL; y++)
                {
                    FrameData.squareData[x][y].timelineFrameNumber = i;
                    FrameData.squareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
                    FrameData.squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P
                }
            }
        }
}

//Function that goes through the timeline and updates/moves frames after a frame is deleted in the middle of the list
void MainWindow::refreshTimelineDelete()
{
    for(int i= V_GLOBAL.G_CURRENTFRAME; i < V_GLOBAL.G_FRAMECOUNT; i++)
        {
            FrameData.squareData = theFrames.RetrieveNode_Middle(i)->squareData; //grabe every frame
            for(int x=0; x<V_GLOBAL.G_ROW; x++)
            {
                for(int y=0; y<V_GLOBAL.G_COL; y++)
                {
                    FrameData.squareData[x][y].timelineFrameNumber = i;
                    FrameData.squareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
                    FrameData.squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P

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

void MainWindow::on_actionSave_2_triggered()
{
    QString fileName = V_GLOBAL.G_FILENAME;

    if(fileName == NULL){
        QString fileName = QFileDialog::getSaveFileName(nullptr,
                    "Save some file", QString(),
                    tr("Tan files (*.tan);; All Files (*)"), nullptr,
                    QFileDialog::ReadOnly | QFileDialog::DontUseNativeDialog);

        if(fileName == NULL)
            return;
    }

     FileOperations::SaveToFile(fileName,&theFrames);
}

void MainWindow::on_actionNew_Project_triggered()
{
    //File -> New Project menu clicked
    //create new project -P
}

// ==== Edit Menue ====

void MainWindow::on_actionClear_Frame_triggered()
{
    on_btn_ClearFrame_clicked(); //from menu -P
}

void MainWindow::on_actionFill_Frame_triggered()
{
    on_btn_FillFrame_clicked(); //from menu -P
}

void MainWindow::on_actionNew_Frame_triggered()
{
    on_btn_NewFrame_clicked(); //from menu -P
}

void MainWindow::on_actionDelete_Frame_triggered()
{
    on_btn_DeleteFrame_clicked(); //from menu -P
}

// ==== Debug menu ====
void MainWindow::on_actionAdd_100_Frames_triggered()
{
    std::cout << "Creating 100 frames" << std::endl;
    // manually create the 100 frames.
    for (int i = 0; i < 100; i++) {
        V_GLOBAL.G_CURRENTFRAME++;
        FrameData.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL, V_GLOBAL.G_CURRENTFRAME);
        fillFrame2(&FrameData, rand()%255, rand()%255, rand()%255);  // Random frame color
        theFrames.AddTail(FrameData);
        V_GLOBAL.G_FRAMECOUNT++; //add a frame to the count
    }
   newFrameHandler();
   initializeEntireTimeline();
}

void MainWindow::on_actionPrint_Frames_triggered()
{
    std::cout << "Printing out all frames" << std::endl;
    theFrames.PrintNode();
}

void MainWindow::on_btn_CopyFrame_clicked()
{
    clipboard = *(theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME));
    clipboard_empty = false;
}

void MainWindow::on_btn_PasteFrame_clicked()
{
    t_FrameData *tempFrameData_current = theFrames.RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);
    if (clipboard_empty) return;
    else
    {
        on_btn_NewFrame_clicked();
        copyFrame(tempFrameData_current, &clipboard);
        ui->dsbox_FrameDur->setValue(clipboard.duration);
        mainGrid.loadFrame(tempFrameData_current); // copy frame into editing grid
        updateTimeline();
    }
}

void MainWindow::on_EyeDropper_clicked()
{
    setCursor(Qt::CrossCursor);
    V_GLOBAL.EyeDropper = true;
}

void MainWindow::drawPalette()
{
    QColor temp;
    for (int x = 0; x < currentPalette->getNumColors(); x++)
    {
        temp = currentPalette->getColor(x);
        if(x < 4)
        {
            PaletteSquare *Top = new PaletteSquare((x*32.5), 0, temp);
            paletteScene->addItem(Top);
        }
        else
        {
            PaletteSquare *Bottom = new PaletteSquare(((x-4)*32.5),32.5,temp);
            paletteScene->addItem(Bottom);
        }
    }
}

void MainWindow::on_btn_DrawRect_clicked()
{
    mainGrid.graphic_drawRect(V_GLOBAL.graphicPoint_1, V_GLOBAL.graphicPoint_2, V_GLOBAL.G_LEFT);
    updateTimeline();
    drawFrame(); //fixed one click lag -P
}
