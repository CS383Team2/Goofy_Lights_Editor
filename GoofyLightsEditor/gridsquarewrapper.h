#ifndef GRIDSQUAREWRAPPER_H
#define GRIDSQUAREWRAPPER_H

#include "gridsquare.h"
#include "globals.h"
#include "framestructure.h"


class gridsquarewrapper
{
public:
    gridsquarewrapper();
    ~gridsquarewrapper();

    GridSquare ** gridSquareData = nullptr;
    QGraphicsScene *gridScenePtr;     // This is created in mainwindow.cpp & passed to this object
    void loadFrame(t_FrameData *frameData);
    void setScene(QGraphicsScene *gridScene);
    void generate(); // creates memory
    void drawGrid();
    void clearGrid();

    void graphic_drawRect(point p1, point p2, QColor fillColor);
};

#endif // GRIDSQUAREWRAPPER_H
