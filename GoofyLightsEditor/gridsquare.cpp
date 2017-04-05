#include "gridsquare.h"
#include <globals.h>
#include <mainwindow.h>

GridSquare::GridSquare()
{
    Selected = false; //constructor
}

GridSquare::~GridSquare()
{
    Selected = false; //destructor lol
}

QRectF GridSquare::boundingRect() const
{
    return QRectF(x,y,22*G_SCALE,22*G_SCALE); //x and y position the square before it's painted -P
    //x, y are top left corner -P
}

void GridSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(square_RGB);

    square_RGB.setRgb(G_RED, G_GREEN, G_BLUE, 255); //grab the color... -P

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

void GridSquare::mousePressEvent(QGraphicsSceneMouseEvent *event) //-P
{
    Selected = true;
    QGraphicsItem::mousePressEvent(event);

    update(); //repaint the grid whenever a cell is clicked
}

