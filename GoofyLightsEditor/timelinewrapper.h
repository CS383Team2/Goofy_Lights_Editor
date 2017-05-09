#ifndef TIMELINEWRAPPER_H
#define TIMELINEWRAPPER_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "framestructure.h"
#include "gridsquarewrapper.h"


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

    // reference pointers loaded from mainwindow
    QGraphicsScene *timelineScenePtr;     // This is created in mainwindow.cpp & passed to this object
    gridsquarewrapper *mainGridPtr;       // Main grid in mainwindow.cpp
    Ui::MainWindow uiPtr;                 // Main window ui

    void setScene(QGraphicsScene *timelineScene, gridsquarewrapper *mainGrid, Ui::MainWindow *UI, QOjbect windowPtr);

    void drawFrame();

    void updateTimeline(); //fix the update lag later -P

    void refreshTimelineAdd();

    void refreshTimelineDelete();

    //BIG draw/refresh/all-in-one function. Handles adding drawing frame, refreshing timeline, drawing to grid, etc. Taken from onbtn_newFrame function.
    void newFrameHandler();

    void initializeEntireTimeline();


};

#endif // TIMELINEWRAPPER_H
