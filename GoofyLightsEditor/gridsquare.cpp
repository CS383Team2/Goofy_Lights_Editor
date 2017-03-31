#include "gridsquare.h"
#include <globals.h>

GridSquare::GridSquare()
{
    Selected = false; //constructor
}

QRectF GridSquare::boundingRect() const
{
    return QRectF(x,y,20,20); //x and y position the square before it's painted -P
}

void GridSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::gray);


    if(Selected)
    {
        if(brush.color() == Qt::gray)
        {
            //QColor(int r, int g, int b, int a = 255) //use this, last argument always 255

            brush.setColor(QColor(G_RED, G_GREEN, G_BLUE, 255)); //HELLO RGB COLOR -green -P

            //brush.setColor(Qt::blue); //old -P
        }
    }

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

void GridSquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Selected = true;
    QGraphicsItem::mousePressEvent(event);
    update(); //repaint the grid whenever a cell is clicked
}
