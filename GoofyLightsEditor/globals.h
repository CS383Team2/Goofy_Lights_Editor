#ifndef GLOBALS_H
#define GLOBALS_H
#include "FrameList.h"

extern double G_SCALE; //magical grid scaling feature :) -P

extern int G_RED;
extern int G_GREEN;
extern int G_BLUE;
extern int G_RED_RIGHT;
extern int G_GREEN_RIGHT;
extern int G_BLUE_RIGHT;

extern int G_FRAMECOUNT;

typedef struct Globals{
    int G_ROW;
    int G_COL;
    QColor G_RIGHT;
    QColor G_LEFT;
    FrameList *G_FRAMELIST;
}V_Goofy;

extern V_Goofy V_GLOBAL;


//extern bool set;

#endif // GLOBALS_H
