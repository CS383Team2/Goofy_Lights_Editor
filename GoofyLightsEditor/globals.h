#ifndef GLOBALS_H
#define GLOBALS_H
#include "FrameList.h"

typedef struct Globals{

    int G_ROW;
    int G_COL;
    int G_FRAMECOUNT = 2;

    QColor G_RIGHT = (Qt::blue); //default to blue jsut for hoots -P
    QColor G_LEFT = (Qt::red); //default to red to match colorwheel default -P

    FrameList *G_FRAMELIST;

}V_Goofy;

extern V_Goofy V_GLOBAL;

#endif // GLOBALS_H
