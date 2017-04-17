#include <iostream>
#include <QApplication>

#include "mainwindow.h"
#include "framestructure.h"      // Defines FrameData structure
#include "FrameList.h"           // Linked List
#include "FrameManipulation.h"   // FrameData manipulations
#include "FileOperations.h"      // File IO
#include <globals.h>             // Defines global structure & externs
#include <sizedialog.h>

V_Goofy V_GLOBAL;  // Global Variables Structure

//int G_FRAMECOUNT = 0; //hah -P

long FrameIDCount = 0;

int main(int argc, char *argv[])
{   
    V_GLOBAL.G_COL = 0; //Initialize global rows and columns
    V_GLOBAL.G_ROW = 0;
    QApplication a(argc, argv);
    //LET'S GET IT STARTED -P
    SizeDialog dialog1;
    dialog1.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint); //You will NOT exit this window your way -P
    dialog1.setModal(true); //Modal blocks input to other windows
    dialog1.exec();

    MainWindow w;
    w.show();
	
	std::cout << "Program end" << endl;
    return a.exec();
}
