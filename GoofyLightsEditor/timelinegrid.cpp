#include "timelinegrid.h"
#include <globals.h>

TimelineGrid::TimelineGrid()
{
    Selected = false; //constructor
}

TimelineGrid::~TimelineGrid()
{
    Selected = false; //destructor lol -P
}

QRectF TimelineGrid::boundingRect() const
{
    //MAIN WINDOW TOO BIG, gonna take the scaling down to 85% -P
    double max = 0;
    if(V_GLOBAL.G_COL > V_GLOBAL.G_ROW)
        max = V_GLOBAL.G_COL;
    else
        max = V_GLOBAL.G_ROW;
    double G_SCALE = ((20.0 / max) * 0.85); //scaled based on a max size of 20x20 -P

    return QRectF(x,y,4*G_SCALE,4*G_SCALE); //x and y position the square before it's painted -P
    //x, y are top left corner -P
}

void TimelineGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(square_RGB); //this get's grabbed from the grid -P

    //yeah

    if(Selected)
    {
            //QColor(int r, int g, int b, int a = 255) //use this, last argument always 255

            brush.setColor(square_RGB); //HELLO RGB COLOR Alpha locked to 255 -green -P

            //The color of any grid square can be had by brush.color() -P
    }

    square_RGB = brush.color();

    QPen pen = square_RGB;

    painter->setPen(pen);
    painter->fillRect(rec,brush);
    painter->drawRect(rec);

    //Fix the FILL BUG: -P
    Selected = false; //simply unselect after each repaint/change. Fixed -P
}

void TimelineGrid::mousePressEvent(QGraphicsSceneMouseEvent *event) //-P
{
    //Selected = true; //you shall not edit the timeline lol
    QGraphicsItem::mousePressEvent(event);

    Selected = true;

    update(); //repaint the grid whenever a cell is clicked
}
