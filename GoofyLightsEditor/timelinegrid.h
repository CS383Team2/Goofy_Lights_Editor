#ifndef TIMELINEGRID_H
#define TIMELINEGRID_H

#include <QPainter>
#include <QGraphicsItem> //What I'm building with this class -Paul
#include <QDebug>

class TimelineGrid : public QGraphicsItem //inherit the public methods of QGraphicsItem -Paul
{
public:
    TimelineGrid();
    ~TimelineGrid();

    QRectF boundingRect() const; //MUST have a bounding rectangle for each square -P

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //paint function -P

    QColor square_RGB = Qt::black;

    bool Selected; //is this square selected? -P

    int x = 0; //drawing locations -P
    int y = 0;

    int timelineFrameNumber = 0; //number used to keep track of indexing of frame for the timeline

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //need to know when the things are clicked on -P
};

#endif // TIMELINEGRID_H
