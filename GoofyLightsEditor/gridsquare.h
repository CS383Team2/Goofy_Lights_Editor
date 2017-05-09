#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include <QPainter>
#include <QGraphicsItem> //What I'm building with this class -Paul
#include <QDebug>

extern bool newGridColor;

class GridSquare : public QGraphicsItem //inherit the public methods of QGraphicsItem -Paul
{
public:
    GridSquare();
    ~GridSquare();

    QRectF boundingRect() const; //MUST have a bounding rectangle for each square -P

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //paint function -P

    QColor square_RGB = Qt::black;

    bool Selected; //is this square selected? -P
    bool ClearSquare;
    bool leftclick;

    int x = 0; //drawing locations -P
    int y = 0;

    // For drawLine feature
    short row_pos = 0;
    short col_pos = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //need to know when the things are clicked on -P
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRIDSQUARE_H
