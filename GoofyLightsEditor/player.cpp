#include "player.h"
#include "ui_player.h"
#include <globals.h>
#include <QThread>
#include <QApplication> //OP weapon -P

Player::Player(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);

    gridScene = new QGraphicsScene(this);
    ui->PlayerGraphicsView->setScene(gridScene); //give the grid to the graphics view -Paul

    // This generates the memory for these grids
    gridGridSquare = new GridSquare*[V_GLOBAL.G_ROW];
    for (int i = 0; i < V_GLOBAL.G_ROW; ++i)
    {
        gridGridSquare[i] = new GridSquare[V_GLOBAL.G_COL];
    }

    max = 0;
    if(V_GLOBAL.G_ROW > V_GLOBAL.G_COL)
        max = V_GLOBAL.G_ROW;
    else
        max = V_GLOBAL.G_COL;
    G_SCALE = ((20.0 / max) * 0.85); //scaled based on a max size of 20x20 -P

    gridScale = 22*G_SCALE;
    timelineScale = 4*G_SCALE;
    g_SPACING = 3; //grid spacing woohooo -P
    t_SPACING = 2; //timeline spacing woohooo -P

    if(V_GLOBAL.G_FRAMECOUNT > 0)
    {
        t_FrameData *tempFrameData = V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(0);   //grab the first frame
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                gridGridSquare[x][y].square_RGB = (*tempFrameData).squareData[x][y].square_RGB; //give the data to the grid -P
                gridGridSquare[x][y].update(); //Fill that frame son -P
            }
        }
        drawGrid();
    }
}

Player::~Player()
{
    //de-allocate the grid
    for (int i = 0; i < V_GLOBAL.G_ROW; ++i)
    {
        delete [] gridGridSquare[i];
    }

    delete ui;    
}

void Player::on_Btn_close_clicked()
{
    close();
}

void Player::on_pushButton_clicked()
{
    if(V_GLOBAL.G_FRAMECOUNT > 0)
    {
        t_FrameData *tempFrameData;
        //loop
        for(int i=1;i<V_GLOBAL.G_FRAMECOUNT; i++)
        {
            tempFrameData = V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(i);   //grab the first frame
            for(int x=0; x<V_GLOBAL.G_ROW; x++)
            {
                for(int y=0; y<V_GLOBAL.G_COL; y++)
                {
                    gridGridSquare[x][y].square_RGB = (*tempFrameData).squareData[x][y].square_RGB; //give the data to the grid -P
                    gridGridSquare[x][y].update(); //Fill that frame son -P
                }
            }
            drawGrid();
            //sleep
            update();
            Sleeper::msleep((tempFrameData->duration) * 1000);
        }
        /*
        tempFrameData = V_GLOBAL.G_FRAMELIST->RetrieveNode_Middle(1);   //grab the first frame
        for(int x=0; x<V_GLOBAL.G_ROW; x++)
        {
            for(int y=0; y<V_GLOBAL.G_COL; y++)
            {
                gridGridSquare[x][y].square_RGB = (*tempFrameData).squareData[x][y].square_RGB; //give the data to the grid -P
                gridGridSquare[x][y].update(); //Fill that frame son -P
            }
        }
        */
    }
}

void Player::drawGrid()
{
    //draw the grid -P
    for(int x=0; x<V_GLOBAL.G_ROW; x++)
    {
        for(int y=0; y<V_GLOBAL.G_COL; y++)
        {
            gridGridSquare[x][y].y = (x*gridScale + x*g_SPACING);
            gridGridSquare[x][y].x = (y*gridScale + y*g_SPACING);
            gridScene->addItem(&gridGridSquare[x][y]);
        }
    }
    qApp->processEvents(); //Extremely OP weapon, fixes all lag, use with caution -P
}
