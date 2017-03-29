#include "gridsquare.h"


GridSquare::GridSquare()
{
    Selected = false; //constructor
}

QRectF GridSquare::boundingRect() const
{
    return QRectF(x,y,20,20);
}

void GridSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::gray);


    if(Selected)
    {
        if(brush.color() == Qt::gray)
        {
            brush.setColor(Qt::blue); //change this to color wheel/data -P
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
