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


    void createActions();
};

#endif // MAINWINDOW_H
