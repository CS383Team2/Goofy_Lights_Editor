#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include "framestructure.h"
#include "FrameList.h"

long FrameIDCount = 0;

// creates the dynamic RGB array
t_RGB** create_RGB(int r, int c);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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

    //Frame 1
    // Generate new rgb_data arrary
    rgb_data = create_RGB(r, c);

    // fill rgb_data for Frame 1
    int color = 0;   // arbritrary data
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
    frames.AddNode(FrameData);  // add this frameData to linked list
    rgb_data  = NULL; // disconnect this pointer from rgb_data


    // next frame Frame 2
    // Generate new rgb_data arrary
    rgb_data = create_RGB(r, c);

     // fill rgb for Frame 2
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
    frames.AddNode(FrameData);
    rgb_data  = NULL; // disconnect this pointer from rgb_data


    std::cout << "Now printing frames" << std::endl;
    // note: frames are in reverse order when added to head
    // print frames
    frames.PrintNode();

    return a.exec();
}

// Function creates a 2d memory element of the RGB struct then passes back the pointer to it.
// source http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
t_RGB** create_RGB(int r, int c)
{
    t_RGB** arr = new t_RGB*[r];
    for(int i = 0; i < r; ++i)
        arr[i] = new t_RGB[c];
    return arr;
}
