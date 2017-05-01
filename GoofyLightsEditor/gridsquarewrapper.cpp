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
    if (gridSquareData) {                          // test if ! null
        for (int i = 0; i < V_GLOBAL.G_ROW; i++)
            delete [] gridSquareData[i];           // delete data arrays
        delete [] gridSquareData;                  // delete pointer array
        gridSquareData = nullptr;                  // null the pointer
    }
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
        // Write gridsquare position
        for (int j = 0; j < V_GLOBAL.G_COL; j++) {
            this->gridSquareData[i][j].row_pos = i;
            this->gridSquareData[i][j].col_pos = j;
        }
    }
}

void gridsquarewrapper::loadFrame(t_FrameData *frameData)
{
    if (frameData == nullptr) {
        QMessageBox msgError;
            msgError.setText("gridsquareWrapper frameData null"),
            msgError.exec();
        return;
    }

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
    int g_SPACING;

    // === From mainwindow.cpp ====
    max_size = 0;
    if(V_GLOBAL.G_ROW > V_GLOBAL.G_COL)
        max_size = V_GLOBAL.G_ROW;
    else
        max_size = V_GLOBAL.G_COL;
    G_SCALE = ((20.0 / max_size) * 0.85); //scaled based on a max size of 20x20 -P

    gridScale = 22*G_SCALE;
    g_SPACING = 3; //grid spacing woohooo -P


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


void gridsquarewrapper::graphic_drawLine(point p1, point p2, QColor fillColor)
{
    // Test if straight line
    if (p1.r == p2.r && p1.c != p2.c) { // if not same point & same row
        std::cout << "endered row drawline" << std::endl;
        int commonPoint = p1.r;                 // the axis that doesnt change
        int direction = (p1.c < p2.c ? 1 : -1); // whether going left-right or right-left
        for (int i = p1.c; i != p2.c; i+=direction) {
            gridSquareData[commonPoint][i].square_RGB = fillColor;
            gridSquareData[commonPoint][i].update();
        }
    }
    else if (p1.c == p2.c && p1.r != p2.r) { // if not same point & same col
        std::cout << "endered row drawline" << std::endl;
        int commonPoint = p1.c;                 // the axis that doesnt change
        int direction = (p1.r < p2.r ? 1 : -1); // whether going top-down or down-up
        for (int i = p1.r; i != p2.r; i+=direction) {
            gridSquareData[i][commonPoint].square_RGB = fillColor;
            gridSquareData[i][commonPoint].update();
        }
    }
    else {
        QMessageBox msgError;
        msgError.setText("DrawLine\nLines must be on the same row or on same column\nThe last two points clicked are used."),
        msgError.exec();
    }
}

void gridsquarewrapper::graphic_drawRect(point p1, point p2, QColor fillColor)
{

    // something is off if done anyway other than top->down. left->right
    if (p1.c > p2.c || p1.r > p2.r || p1.r == p2.r || p1.c == p2.c) {
        QMessageBox msgError;
        msgError.setText("NOT That way. The rectangle will doom this program to a nasty segfault.\nWIP"),
        msgError.exec();
        return;
    }


    int r_direction = (p1.c < p2.c ? 1 : -1); // whether going left-right or right-left
    int c_direction = (p1.r < p2.r ? 1 : -1); // whether going top-down or down-up
    for (int i = p1.r; i != p2.r + r_direction; i+=r_direction) {
        for (int j = p1.c; j != p2.c + c_direction; j+=c_direction) {
            gridSquareData[i][j].square_RGB = fillColor;
            gridSquareData[i][j].update();
        }
    }
}
