#ifndef TIMELINEWRAPPER_H
#define TIMELINEWRAPPER_H


#include "framestructure.h"


class timelinewrapper
{
public:
    timelinewrapper();
    ~timelinewrapper();

    //MAIN WINDOW TOO BIG, gonna take the scaling down to 85% -P
    double max_size;
    double G_SCALE;
    int timelineScale;
    int t_SPACING;

    TimelineGrid ** gridSquareData = NULL;
    QGraphicsScene *timelineScenePtr;     // This is created in mainwindow.cpp & passed to this object

    void setScene(QGraphicsScene *timelineScene);

    void drawFrame();

    void updateTimeline(); //fix the update lag later -P

    void refreshTimelineAdd();

    void refreshTimelineDelete();

    //BIG draw/refresh/all-in-one function. Handles adding drawing frame, refreshing timeline, drawing to grid, etc. Taken from onbtn_newFrame function.
    void newFrameHandler();


};

#endif // TIMELINEWRAPPER_H
