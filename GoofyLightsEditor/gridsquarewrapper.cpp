#include "gridsquarewrapper.h"
#include "globals.h"

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <gridsquare.h>

gridsquarewrapper::gridsquarewrapper()
{

}

gridsquarewrapper::~gridsquarewrapper()
{
    // delete memory
}

// must call this and set gridscene
void gridsquarewrapper::setScene(QGraphicsScene *gridScene)
{
    // link gridScene to internal pointer
    this->gridScenePtr = gridScene;
}

void gridsquarewrapper::generate()
{
    // Generates the memory for these grids
    this->gridSquareData = new GridSquare*[V_GLOBAL.G_ROW];
    for (int i = 0; i < V_GLOBAL.G_ROW; ++i)
    {
        this->gridSquareData[i] = new GridSquare[V_GLOBAL.G_COL];
    }
}

void gridsquarewrapper::loadFrame(t_FrameData *frameData)
{
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            this->gridSquareData[x][y].square_RGB = (*frameData).squareData[x][y].square_RGB; //give the data to the grid -P
            gridSquareData[x][y].update(); //Fill that frame son -P
        }
    }
}

void gridsquarewrapper::drawGrid()
{
    // === Frome mainwindow.h ===
    double max_size;
    double G_SCALE;
    int gridScale;
    int timelineScale;
    int g_SPACING;
    int t_SPACING;

    // === From mainwindow.cpp ====
    max_size = 0;
    if(V_GLOBAL.G_ROW > V_GLOBAL.G_COL)
        max_size = V_GLOBAL.G_ROW;
    else
        max_size = V_GLOBAL.G_COL;
    G_SCALE = ((20.0 / max_size) * 0.85); //scaled based on a max size of 20x20 -P

    gridScale = 22*G_SCALE;
    timelineScale = 4*G_SCALE;
    g_SPACING = 3; //grid spacing woohooo -P
    t_SPACING = 2; //timeline spacing woohooo -P


    //draw the grid -P
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            this->gridSquareData[x][y].y = (x*gridScale + x*g_SPACING);
            this->gridSquareData[x][y].x = (y*gridScale + y*g_SPACING);
            gridScenePtr->addItem(&gridSquareData[x][y]);
        }
    }
}
