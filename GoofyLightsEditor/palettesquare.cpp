#include "palettesquare.h"
#include <globals.h>
#include <mainwindow.h>

PaletteSquare::PaletteSquare(int pos_x, int pos_y, QColor squareColor)
{
    x = pos_x;
    y = pos_y;
    square_RGB = squareColor;
    Selected = false;
}

PaletteSquare::~PaletteSquare()
{
    Selected = false;
}

QRectF PaletteSquare::boundingRect() const
{
    return QRectF(x,y,25,25);
}

void PaletteSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(square_RGB);

    if (Selected)
       if (leftclick)
          V_GLOBAL.G_LEFT = square_RGB;
       else
          V_GLOBAL.G_RIGHT = square_RGB;
    brush.setColor(square_RGB);
    square_RGB = brush.color();

    QPen pen = square_RGB;

    painter->setPen(pen);
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
    Selected = false;

    Rcolor->square_RGB = V_GLOBAL.G_RIGHT;
    Lcolor->square_RGB = V_GLOBAL.G_LEFT;

    // Update GUI
    Rcolor->update();
    Lcolor->update();
}

void PaletteSquare::mousePressEvent(QGraphicsSceneMouseEvent *event) //-P
{
    if (event->button() == Qt::RightButton)
        leftclick = false;
    else
        leftclick = true;
    Selected = true;

    V_GLOBAL.G_TIMELINESELECTED = false;

    QGraphicsItem::mousePressEvent(event);
}

void PaletteSquare::mousePressEvent(QMouseEvent *event)
{
    update();
}
