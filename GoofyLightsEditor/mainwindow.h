#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <gridsquare.h>
#include "FrameList.h"
#include <colorwheel.h>
#include <globals.h>
#include <timelinegrid.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GridSquare **gridGridSquare = new GridSquare*[G_COL];  //Type is GridSquare, square is object
    TimelineGrid **timelineTimelineGrid = new TimelineGrid*[G_COL];  //Type is TimelineGrid, square2 is object
    t_FrameData FrameData;  // THE frame data (this is in mainwindow.h) -P

    void gridToFrameData();
    void FrameDataToGrid(); //stitching rubbish -P
    void updateTimeline();

private slots:
    void on_actionSave_As_triggered();

    void on_actionOpenProject_triggered();


    void on_sbox_ValueRed_editingFinished();

    void on_sbox_ValueGreen_editingFinished();

    void on_sbox_ValueBlue_editingFinished();

    void mousePressEvent(QMouseEvent *event);

    void on_btn_FillFrame_clicked();

    void on_btn_ClearFrame_clicked();

    void on_btn_ClearFrame_released();

    void on_btn_ClearFrame_pressed();


private:
    Ui::MainWindow *ui;

    QGraphicsScene *gridScene; //grid -P

    QGraphicsScene *timelineScene; //timeline -P


    void createActions();
};

#endif // MAINWINDOW_H
