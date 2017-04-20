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

    return a.exec();
}
