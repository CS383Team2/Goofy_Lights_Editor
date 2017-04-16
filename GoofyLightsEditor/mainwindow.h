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

    //MAIN WINDOW TOO BIG, gonna take the scaling down to 85% -P
    double max;
    double G_SCALE;
    int gridScale;
    int timelineScale;
    int g_SPACING;
    int t_SPACING;


    GridSquare **gridGridSquare; // = new GridSquare*[V_GLOBAL.G_ROW];  //Type is GridSquare, square is object

    //TimelineGrid **timelineTimelineGrid = new TimelineGrid*[V_GLOBAL.G_ROW];  //Type is TimelineGrid, square2 is object


    TimelineGrid ** tempSquareData = new TimelineGrid*[V_GLOBAL.G_ROW];
    TimelineGrid ** tempSquareData2 = new TimelineGrid*[V_GLOBAL.G_ROW];

    t_FrameData FrameData;  // THE frame data (this is in mainwindow.h) -P

    t_FrameData CurrentFrameData;


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

    void on_btn_ClearFrame_released();

    void on_btn_ClearFrame_pressed();


    void on_btn_NewFrame_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *gridScene; //grid -P

    QGraphicsScene *timelineScene; //timeline -P

    QGraphicsScene *currentcolorsScene;

    void createActions();
};

#endif // MAINWINDOW_H
