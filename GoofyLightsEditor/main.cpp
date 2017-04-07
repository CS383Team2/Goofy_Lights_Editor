#include <iostream>
#include "mainwindow.h"
#include <QApplication>

#include "framestructure.h"
#include "FrameList.h"
#include "FrameManipulation.h"
#include "FileOperations.h"
#include <globals.h>
#include <sizedialog.h>

int G_COL = 0; //initialize globals -P
int G_ROW = 0;
double G_SCALE = 0;

int G_RED = 255;
int G_GREEN = 0; //fixed -P
int G_BLUE = 0;

int G_FRAMECOUNT = 0; //hah -P


long FrameIDCount = 0;

// creates the dynamic RGB array
t_RGB** create_RGB(int r, int c);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LET'S GET IT STARTED -P
    SizeDialog dialog1;
    dialog1.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint); //You will NOT exit this window your way -P
    dialog1.setModal(true); //YOU SHALL NOT CLICK OUTSIDE OF THIS WINDOW -P
    dialog1.exec(); //execute pls -P

    //read in a file here probably -P

    MainWindow w;
    w.show();

    // linked list test
    std::cout << "FrameList testing" << std::endl;

    // set arbitrary grid size
    int r = 5;
    int c = 3;
    t_RGB ** rgb_data;

    t_FrameData FrameData;  // Local frame data
    FrameList frames(r, c); // linked list for frame data. r c for print function

    //Frame 0
    // Generate new rgb_data arrary
    rgb_data = create_RGB(r, c);

    // fill rgb_data for Frame 0
    unsigned short color = 0;   // arbritrary data
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            rgb_data[i][j].R = color++;
            rgb_data[i][j].G = color++;
            rgb_data[i][j].B = color++;
        }
    }
    FrameData.ID = FrameIDCount++;
    FrameData.durration = 123;
    FrameData.data = rgb_data;
    frames.AddTail(FrameData);  // add this frameData to linked list
    rgb_data  = NULL; // disconnect this pointer from rgb_data


    // next frame Frame 1
    // Generate new rgb_data arrary
    rgb_data = create_RGB(r, c);

     // fill rgb for Frame 1
    color = 100; // arbritrary increment to make data different
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            rgb_data[i][j].R = color++;
            rgb_data[i][j].G = color++;
            rgb_data[i][j].B = color++;
        }
    }
    FrameData.ID = FrameIDCount++;
    FrameData.durration = 212;
    FrameData.data = rgb_data;
    frames.AddTail(FrameData);
    rgb_data  = NULL; // disconnect this pointer from rgb_data


    // next frame Frame 2
    rgb_data = create_RGB(r, c);
    FrameData.ID = FrameIDCount++;
    FrameData.durration = 214;
    FrameData.data = rgb_data;
    fillFrame2(FrameData, 21, 32, 45);
    frames.AddTail(FrameData);

    // copyFrame Test
    t_FrameData newFrame;
    rgb_data = create_RGB(r, c);
    newFrame.ID = FrameIDCount++;
    newFrame.durration = 217;
    newFrame.data = rgb_data;
    copyFrame(newFrame, FrameData);
    frames.AddTail(newFrame);


    frames.PrintNode();


    // std::cout << "Now printing frames" << std::endl;
    // note: frames are in reverse order when added to head
    // print frames
    // frames.PrintNode();
    // FrameList frameList = FileOperations::LoadFromFile("autofill.proj");
    // frameList.PrintNode();
    FileOperations::SaveToFile(frames, "autofill.proj");


    frames.DeleteList();
    std::cout << "Program end" << std::endl;
    return a.exec();
}
