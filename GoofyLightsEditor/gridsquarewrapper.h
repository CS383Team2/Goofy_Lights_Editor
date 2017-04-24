#ifndef GRIDSQUAREWRAPPER_H
#define GRIDSQUAREWRAPPER_H

#include "gridsquare.h"
#include "framestructure.h"


class gridsquarewrapper
{
public:
    gridsquarewrapper();
    ~gridsquarewrapper();

    GridSquare ** gridSquareData;
    QGraphicsScene *gridScenePtr;     // This is created in mainwindow.cpp & passed to this object
    void loadFrame(t_FrameData *frameData);
    void setScene(QGraphicsScene *gridScene);
    void generate(); // creates memory
    void drawGrid();
};

#endif // GRIDSQUAREWRAPPER_H
