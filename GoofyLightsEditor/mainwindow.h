#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <gridsquare.h>
#include "FrameList.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSave_As_triggered();

    FrameList on_actionOpenProject_triggered();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    //excuse the mess for now -P
    GridSquare *square1; //create an object for a square
    GridSquare *square2; //create an object for a square
    GridSquare *square3; //create an object for a square
    GridSquare *square4; //create an object for a square
    GridSquare *square5; //create an object for a square
    GridSquare *square6; //create an object for a square
    GridSquare *square7; //create an object for a square
    GridSquare *square8; //create an object for a square
    GridSquare *square9; //create an object for a square
    GridSquare *square10; //create an object for a square
    GridSquare *square11; //create an object for a square
    GridSquare *square12; //create an object for a square
    GridSquare *square13; //create an object for a square
    GridSquare *square14; //create an object for a square
    GridSquare *square15; //create an object for a square
    GridSquare *square16; //create an object for a square



    void createActions();
};

#endif // MAINWINDOW_H
