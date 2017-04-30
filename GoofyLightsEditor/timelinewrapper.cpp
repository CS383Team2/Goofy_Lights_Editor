#include "timelinewrapper.h"
#include "framestructure.h"
#include "globals.h"

#include <QMainWindow>
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
void timelinewrapper::setScene(QGraphicsScene *gridScene)
{
    // link gridScene to internal pointer
    this->timelineScenePtr = gridScene;
}



void timelinewrapper::drawFrame()
{
    int i = V_GLOBAL.G_CURRENTFRAME;
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
       for(int y=0; y<V_GLOBAL.G_COL; y++)
       {
           FrameData.squareData[x][y].y = (x*timelineScale + x*t_SPACING); //timeline magic about to happen here -P
           FrameData.squareData[x][y].x = (y*timelineScale + y*t_SPACING) + (i*110); // magic -P
           timelineScenePtr->addItem(&(FrameData.squareData[x][y])); //timeline painting here -P
       }
     }
}

void timelinewrapper::updateTimeline() //fix the update lag later -P
{
    t_FrameData *tempFrameData = V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(V_GLOBAL.G_CURRENTFRAME);   //grab the current frame
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            (*tempFrameData).squareData[x][y].square_RGB = mainGrid.gridSquareData[x][y].square_RGB;
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

}

void timelinewrapper::refreshTimelineDelete()
{

}

//BIG draw/refresh/all-in-one function. Handles adding drawing frame, refreshing timeline, drawing to grid, etc. Taken from onbtn_newFrame function.
void timelinewrapper::newFrameHandler()
{

}






