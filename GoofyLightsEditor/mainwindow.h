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

    GridSquare **square = new GridSquare*[G_COL];  //Type is GridSquare, square is object
    TimelineGrid **square2 = new TimelineGrid*[G_COL];  //Type is TimelineGrid, square2 is object
    t_FrameData FrameData;  // THE frame data (this is in mainwindow.h) -P

    void gridToFrameData();
    void FrameDataToGrid(); //stitching rubbish -P

private slots:
    void on_actionSave_As_triggered();

    FrameList on_actionOpenProject_triggered();


    void on_spinBox_editingFinished();

    void on_spinBox_2_editingFinished();

    void on_spinBox_3_editingFinished();

    void mousePressEvent(QMouseEvent *event);

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_21_released();

    void on_pushButton_21_pressed();


private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene1; //grid -P

    QGraphicsScene *scene2; //timeline -P


    void createActions();
};

#endif // MAINWINDOW_H
