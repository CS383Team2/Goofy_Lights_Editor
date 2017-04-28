#ifndef PALETTESQUARE_H
#define PALETTESQUARE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QWidget>
#include <QDebug>


class PaletteSquare : public QGraphicsItem
{
public:
    PaletteSquare( int pos_x, int pos_y, QColor squareColor);
    ~PaletteSquare();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor square_RGB;

    bool Selected;
    bool leftclick;

    int x;
    int y;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // PALETTESQUARE_H
