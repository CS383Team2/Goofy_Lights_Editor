#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <gridsquare.h>
#include <palettesquare.h>
#include <palette.h>
#include "FrameList.h"
#include <colorwheel.h>
#include <globals.h>
#include <timelinegrid.h>

extern PaletteSquare *Rcolor;
extern PaletteSquare *Lcolor;

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
    double max_size;
    double G_SCALE;
    int timelineScale;
    int t_SPACING;


    GridSquare **gridGridSquare;     //Type is GridSquare, square is object
    t_FrameData FrameData;           // THE frame data (this is in mainwindow.h) -P
    t_FrameData CurrentFrameData;
    t_FrameData clipboard;
    bool clipboard_empty = true;
    QRect redSquare; //in .h -P

    //Updates timeline with current grid square
    void updateTimeline();

    //Function used to initialize timeline when many frames are being added at once
    void initializeEntireTimeline();

private slots:
    void on_actionSave_As_triggered();

    void on_actionOpenProject_triggered();

    void on_sbox_ValueRed_editingFinished();

    void on_sbox_ValueGreen_editingFinished();

    void on_sbox_ValueBlue_editingFinished();

    void mousePressEvent(QMouseEvent *event);

    void on_btn_FillFrame_clicked();

    void on_btn_ClearFrame_clicked();

    //Creates first frame of a new project or frame 0
    void createFirstFrame();

    void on_btn_NewFrame_clicked();

    void on_btn_DeleteFrame_clicked();

    void on_btn_TransRight_clicked();

    void insertFrame(t_FrameData newFrame);

    void on_dsbox_FrameDur_valueChanged(double arg1);

    //Processes translate button presses and performs actual translation actions
    void ProcessTranslateFrame(int DIR);

    void on_btn_TransUP_clicked();

    void on_btn_TransLeft_clicked();

    void on_btn_TransDwn_clicked();

    void on_btn_TransDwnRight_clicked();

    void on_btn_TransDwnLeft_clicked();

    void on_btn_TransUpLeft_clicked();

    void on_btn_TransUpRight_clicked();

    void on_btn_RepeatFrame_clicked();

    //Big function that handles all the actions that are needed related to drawing when a new frame is
    //added. This includes adding the frame to the timeline, updating the timeline to fit the new frame,
    //drawing the square around the new frame, and updating the grid with the new frame.
    void newFrameHandler();

    //Adds new frame to timeline
    void drawFrame();

    //Refreshes/updates the timeline after a new frame is added. This changes the timelinenumber of frames
    //if needed to match the new indexing with the frame being added.
    void refreshTimelineAdd();

    void on_btn_PlayPause_clicked();

    void on_actionAbout_triggered(); //Nick, check this out

    void on_actionDocumentation_triggered();

    void on_actionPlay_All_triggered();

    void on_actionSave_2_triggered();

    void on_actionNew_Project_triggered();

    void on_actionClear_Frame_triggered();

    void on_actionFill_Frame_triggered();

    void on_actionNew_Frame_triggered();

    void on_actionDelete_Frame_triggered();

    void on_actionAdd_100_Frames_triggered();

    void on_actionPrint_Frames_triggered();

    void on_btn_CopyFrame_clicked();

    void on_btn_PasteFrame_clicked();

    void on_EyeDropper_clicked();

    void drawPalette();

    void on_btn_DrawRect_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *gridScene; //grid -P

    QGraphicsScene *timelineScene; //timeline -P

    QGraphicsScene *currentcolorsScene;

    QGraphicsScene *paletteScene;

    //Variable used to keep track if translate button was clicked so that newFrameHandler is
    //only run once as it is in both the translate frame button click function and the new frame button
    //press function.
    bool translateClicked = false;

    void createActions();
};

#endif // MAINWINDOW_H
