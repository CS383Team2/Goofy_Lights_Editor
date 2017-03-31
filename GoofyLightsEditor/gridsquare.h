#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include <QPainter>
#include <QGraphicsItem> //What I'm building with this class -Paul
#include <QDebug>


class GridSquare : public QGraphicsItem //inherit the public methods of QGraphicsItem -Paul

{
public:
    GridSquare();

    QRectF boundingRect() const; //MUST have a bounding rectangle for each square -P

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //paint function -P


    bool Selected; //is this square selected? -P

    int x = 0; //drawing locations -P
    int y = 0;

    //row and column locations are not used, as the frames are just numbered sequentially.... bleh. -P
    int rL = 0; //row location -P
    int cL = 0; //column location -P

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //need to know when the things are clicked on -P
};

#endif // GRIDSQUARE_H
