#include <iostream>
#include "mainwindow.h"
#include <QApplication>

#include "framestructure.h"
#include "FrameList.h"
#include "FrameManipulation.h"
#include "FileOperations.h"

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
    FrameData.r = r;
    FrameData.c = c;
    FrameList frames(r, c); // linked list for frame data. r c for print function

    //Frame 1
    // Generate new rgb_data arrary
    rgb_data = create_RGB(r, c);

    // fill rgb_data for Frame 1
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
    frames.AddTail(FrameData);
    rgb_data  = NULL; // disconnect this pointer from rgb_data


    // fillFrame Test
    rgb_data = create_RGB(r, c);
    FrameData.ID = FrameIDCount++;
    FrameData.durration = 214;
    FrameData.data = rgb_data;
    fillFrame2(FrameData, 21, 32, 45);
    frames.AddTail(FrameData);

    // add breakpoint here. rgb_data set 'change disp val formate' to array 10
    //delete_RGB(rgb_data, r, c);
    std::cout << "printing" << std::endl;
	frames.PrintNode();
    std::cout << "Deleting node 1" << std::endl;
	frames.DeleteNode_Middle(1);
    std::cout << "printing" << std::endl;


    frames.PrintNode();


    // std::cout << "Now printing frames" << std::endl;
    // note: frames are in reverse order when added to head
    // print frames
    // frames.PrintNode();
    // FrameList frameList = FileOperations::LoadFromFile("autofill.proj");
    // frameList.PrintNode();
    // FileOperations::SaveToFile(frameList, "autofill.proj");


    std::cout << "Program end" << std::endl;
    frames.DeleteList();
    return a.exec();
}
