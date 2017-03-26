#include <iostream>
#include "mainwindow.h"
#include <QApplication>
#include "framestructure.h"
#include "FrameList.h"

long FrameIDCount = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();


    // linked list test
    std::cout << "FrameList testing" << std::endl;

    //Frame 1
    t_FrameData FrameData;
    FrameList frames, history;
    FrameData.ID = FrameIDCount++;
    FrameData.durration = 123;
    frames.AddNode(FrameData);

    // next frame Frame 2
    FrameData.ID = FrameIDCount++;
    FrameData.durration = 212;
    frames.AddNode(FrameData);

    std::cout << "Now printing frames" << std::endl;
    // note: frames are in reverse order when added to head
    // print frames
    frames.PrintNode();

    return a.exec();
}
