#include "gridsquare.h"
#include <globals.h>

GridSquare::GridSquare()
{
    Selected = false; //constructor
}

QRectF GridSquare::boundingRect() const
{
    return QRectF(x,y,22,22); //x and y position the square before it's painted -P
}

void GridSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(square_RGB);

    square_RGB.setRgb(G_RED, G_GREEN, G_BLUE, 255); //grab the color... -P

    if(Selected)
    {
        //if(brush.color() == Qt::black)
        if(1)
        {
            //QColor(int r, int g, int b, int a = 255) //use this, last argument always 255

            brush.setColor(square_RGB); //HELLO RGB COLOR Alpha locked to 255 -green -P

            //The color of any grid square can be had by brush.color() -P
        }
    }

    square_RGB = brush.color();
    
    QPen pen = square_RGB;

    painter->setPen(pen);
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

void GridSquare::mousePressEvent(QGraphicsSceneMouseEvent *event) //-P
{
    Selected = true;
    QGraphicsItem::mousePressEvent(event);

    update(); //repaint the grid whenever a cell is clicked
}

