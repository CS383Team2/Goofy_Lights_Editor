#include "gridsquare.h"
#include <globals.h>
#include <mainwindow.h>

GridSquare::GridSquare()
{
    Selected = false; //constructor
    ClearSquare = false;
    Palette = false;
}

GridSquare::GridSquare(bool if_palette)
{
    Selected = false; //constructor
    ClearSquare = false;
    Palette = if_palette;
}

GridSquare::~GridSquare()
{
    Selected = false; //destructor lol
}

QRectF GridSquare::boundingRect() const
{
    //MAIN WINDOW TOO BIG, gonna take the scaling down to 85% -P
    double max = 0;
    if(V_GLOBAL.G_COL > V_GLOBAL.G_ROW)
        max = V_GLOBAL.G_COL;
    else
        max = V_GLOBAL.G_ROW;
    double G_SCALE = ((20.0 / max) * 0.85); //scaled based on a max size of 20x20 -P

    return QRectF(x,y,22*G_SCALE,22*G_SCALE); //x and y position the square before it's painted -P
    //x, y are top left corner -P
}

void GridSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(square_RGB);

    if(Selected)
    {
        if (ClearSquare)
        {
            square_RGB.setRgb(0, 0, 0, 255);
            ClearSquare = false;
        }
        else
            if (leftclick) square_RGB.setRgb(V_GLOBAL.G_LEFT.red(), V_GLOBAL.G_LEFT.green(), V_GLOBAL.G_LEFT.blue(), 255); //grab the color... -P
            else  square_RGB.setRgb(V_GLOBAL.G_RIGHT.red(), V_GLOBAL.G_RIGHT.green(), V_GLOBAL.G_RIGHT.blue(), 255);
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

void GridSquare::mousePressEvent(QGraphicsSceneMouseEvent *event) //-P
{
    if (Palette == true)
        return;
    if (event->button() == Qt::RightButton)
        leftclick = false;
    else
        leftclick = true;
    Selected = true;

    V_GLOBAL.G_TIMELINESELECTED = false;

    QGraphicsItem::mousePressEvent(event);


    update(); //repaint the grid whenever a cell is clicked
}

void GridSquare::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Selected = true;
    ClearSquare = true;
    QGraphicsItem::mouseDoubleClickEvent(event);

    update();
}
