#include "timelinewrapper.h"
#include "framestructure.h"
#include "globals.h"
#include "gridsquarewrapper.h"
#include "FrameManipulation.h"

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
void timelinewrapper::setScene(QGraphicsScene *gridScene, gridsquarewrapper *mainGrid)
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

}

void timelinewrapper::refreshTimelineDelete()
{

}

//BIG draw/refresh/all-in-one function. Handles adding drawing frame, refreshing timeline, drawing to grid, etc. Taken from onbtn_newFrame function.
void timelinewrapper::newFrameHandler()
{

}






