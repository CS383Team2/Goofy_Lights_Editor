#ifndef GLOBALS_H
#define GLOBALS_H
#include "FrameList.h"

typedef struct Globals{

    int G_ROW;
    int G_COL;
    int G_FRAMECOUNT = 0;

    QColor G_RIGHT = (Qt::blue); //default to blue jsut for hoots -P
    QColor G_LEFT = (Qt::red); //default to red to match colorwheel default -P
    bool EyeDropper = false;

    FrameList * G_FRAMELIST = new FrameList();

    int G_CURRENTFRAME = 0;
    bool G_TIMELINESELECTED = false;

    QString G_FILENAME = QString();

}V_Goofy;

extern V_Goofy V_GLOBAL;

#endif // GLOBALS_H
