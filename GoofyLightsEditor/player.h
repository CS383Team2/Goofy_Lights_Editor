#ifndef PLAYER_H
#define PLAYER_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <gridsquare.h>

namespace Ui {
class Player;
}

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

class Player : public QDialog
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = NULL);
    ~Player();

    GridSquare **gridGridSquare;

    double max;
    double G_SCALE;
    int gridScale;
    int timelineScale;
    int g_SPACING;
    int t_SPACING;

private slots:
    void on_Btn_close_clicked();

    void on_pushButton_clicked();

    void drawGrid();

private:
    Ui::Player *ui;

    QGraphicsScene *gridScene; //grid -P
};

#endif // PLAYER_H
