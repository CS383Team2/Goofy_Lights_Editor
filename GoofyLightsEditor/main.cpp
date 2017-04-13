#include <iostream>
#include "mainwindow.h"
#include <QApplication>

#include "framestructure.h"
#include "FrameList.h"
#include "FrameManipulation.h"
#include "FileOperations.h"
#include <globals.h>
#include <sizedialog.h>

V_Goofy V_GLOBAL;

//int G_FRAMECOUNT = 0; //hah -P

long FrameIDCount = 0;

// creates the dynamic RGB array
TimelineGrid** create_RGB(int r, int c);

int main(int argc, char *argv[])
{   
    V_GLOBAL.G_COL = 0; //Initialize global rows and columns
    V_GLOBAL.G_ROW = 0;
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
    //Arbitrary size for testing only
    //G_ROW = 10;
    //G_COL = 10;

    TimelineGrid **rgb_data = new TimelineGrid*[V_GLOBAL.G_ROW]; //Initial TimelineGrid testing

    for (int i = 0; i < V_GLOBAL.G_ROW; ++i)
    {
        rgb_data[i] = new TimelineGrid[V_GLOBAL.G_COL];
    }

    /*
    t_FrameData FrameData;  // Local frame data
    FrameList frames(V_GLOBAL.G_ROW, V_GLOBAL.G_COL); // linked list for frame data. r c for print function
    //V_GLOBAL.G_FRAMELIST = &frames;

    //Frame 0
    // Generate new rgb_data arrary
    //rgb_data = create_RGB(r, c);

    // fill rgb_data for Frame 0
    unsigned short color = 0;   // arbritrary data
    for (int i = 0; i < V_GLOBAL.G_ROW; i++){
        for (int j = 0; j < V_GLOBAL.G_COL; j++){
            rgb_data[i][j].square_RGB.setRed(color++);
            rgb_data[i][j].square_RGB.setGreen(color);
            rgb_data[i][j].square_RGB.setBlue(color);

        }
    }
    FrameData.ID = FrameIDCount++;
    FrameData.duration = 123;
    FrameData.squareData = rgb_data;
    translateFrame(FrameData, D_UP);
    frames.AddTail(FrameData);  // add this frameData to linked list
    rgb_data  = NULL; // disconnect this pointer from rgb_data


    // next frame Frame 1
    // Generate new rgb_data arrary
    rgb_data = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);

     // fill rgb for Frame 1
    color = 0; // arbritrary increment to make data different
    for (int i = 0; i < V_GLOBAL.G_ROW; i++){
        for (int j = 0; j < V_GLOBAL.G_COL; j++){
            rgb_data[i][j].square_RGB.setRed(color++);
            rgb_data[i][j].square_RGB.setGreen(color);
            rgb_data[i][j].square_RGB.setBlue(color);
        }
    }
    FrameData.ID = FrameIDCount++;
    FrameData.duration = 212;
    FrameData.squareData = rgb_data;
    frames.AddTail(FrameData);
    rgb_data  = NULL; // disconnect this pointer from rgb_data


    // next frame Frame 2
    rgb_data = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);
    FrameData.ID = FrameIDCount++;
    FrameData.duration = 214;
    FrameData.squareData = rgb_data;
    //fillFrame2(FrameData, 21, 32, 45);
    frames.AddTail(FrameData);

    // copyFrame Test Frame 3
    t_FrameData newFrame;
    rgb_data = create_RGB(V_GLOBAL.G_ROW, V_GLOBAL.G_COL);
    newFrame.ID = FrameIDCount++;
    newFrame.duration = 217;
    newFrame.squareData = rgb_data;
    copyFrame(newFrame, FrameData);
    frames.AddTail(newFrame);

    // std::cout << "Now printing frames" << std::endl;
    frames.PrintNode();
    //FrameList frameList(V_GLOBAL.G_ROW, V_GLOBAL.G);
    //FileOperations::LoadFromFile("autofill.proj", &frameList);
    //frameList.PrintNode();
    //FileOperations::SaveToFile(frames, "autofill.proj");

    frames.DeleteList();
    std::cout << "Program end" << std::endl;
    */

    return a.exec();
}
