#include "timelinewrapper.h"
#include "framestructure.h"
#include "globals.h"
#include "gridsquarewrapper.h"
#include "FrameManipulation.h"

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <gridsquare.h>

timelinewrapper::timelinewrapper()
{

}

timelinewrapper::~timelinewrapper()
{
    // delete memory if needed
}

// must call this and set gridscene
void timelinewrapper::setScene(QGraphicsScene *gridScene, gridsquarewrapper *mainGrid, Ui::MainWindow *UI)
{
    // link gridScene to internal pointer
    this->timelineScenePtr = gridScene;
    this->mainGridPtr  = mainGrid;
}



void timelinewrapper::drawFrame()
{
    t_FrameData FrameDatatemp;
    FrameDatatemp.squareData = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);
    int i = V_GLOBAL.G_CURRENTFRAME;
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
       for(int y=0; y<V_GLOBAL.G_COL; y++)
       {
           FrameDatatemp.squareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
           FrameDatatemp.squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P
           timelineScenePtr->addItem(&(FrameDatatemp.squareData[x][y])); //timeline painting here -P
       }
     }
    // free FraemDatatemp squareData?
}

void timelinewrapper::updateTimeline() //fix the update lag later -P
{
    t_FrameData *tempFrameData = V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the current frame
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            (*tempFrameData).squareData[x][y].square_RGB = (*mainGridPtr).gridSquareData[x][y].square_RGB;
            (*tempFrameData).squareData[x][y].update();
        }
    }

    //ui->dsbox_FrameDur->setValue((*tempFrameData).duration);

    double currtime = 0.0;
    for (int i = 0; i < V_GLOBAL.G_CURRENTFRAME; i++) //This is broken
        currtime += V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(i)->duration;
    //ui->dsbox_CurrTime->setValue(currtime);
}

void timelinewrapper::refreshTimelineAdd()
{
    for(int i= V_GLOBAL.G_CURRENTFRAME+1; i < V_GLOBAL.G_FRAMECOUNT; i++)
        {
            t_FrameData FrameDatatemp;
            FrameDatatemp.squareData = V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(i)->squareData; //grab every frame
            for(int x=0; x<V_GLOBAL.G_ROW; x++)
            {
                for(int y=0; y<V_GLOBAL.G_COL; y++)
                {
                    FrameDatatemp.squareData[x][y].timelineFrameNumber = i;
                    FrameDatatemp.squareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
                    FrameDatatemp.squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P
                }
            }
        }
}

void timelinewrapper::refreshTimelineDelete()
{
   // not defined in mainwindow.cpp. Candidate for code cleanup
}

//BIG draw/refresh/all-in-one function. Handles adding drawing frame, refreshing timeline, drawing to grid, etc. Taken from onbtn_newFrame function.
void timelinewrapper::newFrameHandler()
{
    this->drawFrame();
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
    timelineScenePtr->addRect((((i)*redSpacingX)-10),(-10),redSizeX,redSizeY,clearPen,(Qt::NoBrush));
    }
    timelineScenePtr->addRect((((V_GLOBAL.G_CURRENTFRAME)*redSpacingX)-10),(-10),redSizeX,redSizeY,redPen,(Qt::NoBrush));

    t_FrameData *tempFrameData_current = V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);
    mainGridPtr->loadFrame(tempFrameData_current); // copy frame into editing grid

    //show duration of new frame
    uiPtr.dsbox_FrameDur->setValue((*tempFrameData_current).duration);


    //Scroll -P
    qApp->processEvents();
    //qDebug() << "Current frame: " << V_GLOBAL.G_CURRENTFRAME << "Framecount: " << V_GLOBAL.G_FRAMECOUNT << endl;
    if((V_GLOBAL.G_CURRENTFRAME+1) == V_GLOBAL.G_FRAMECOUNT)
    uiPtr.gView_Timeline->horizontalScrollBar()->setValue(( uiPtr.gView_Timeline->horizontalScrollBar()->maximum()));
    //Keep timeline scrolled all the way to the RIGHT -P
}

void timelinewrapper::initializeEntireTimeline()
{
    timelineScenePtr = NULL;
    delete timelineScenePtr;

    timelineScenePtr = new QGraphicsScene(); //QOjbect *parent
    uiPtr.gView_Timeline->setScene(timelineScenePtr); //give the timeline to the graphics view -Paul

    timelineScenePtr->update();

    for(int i=0; i < V_GLOBAL.G_FRAMECOUNT; i++) //loop through ALL the frames -P
    {
        t_FrameData FrameDatatemp;
        FrameDatatemp.squareData = V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(i)->squareData; //grab every frame
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                FrameDatatemp.squareData[x][y].timelineFrameNumber = i;
                FrameDatatemp.squareData[x][y].y = (x*timelineScale + x*t_SPACING);
                FrameDatatemp.squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110);
                timelineScenePtr->addItem(&(FrameDatatemp.squareData[x][y])); //timeline painting here -P
            }
        }
    }
}






