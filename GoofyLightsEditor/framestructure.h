#ifndef FRAMESTRUCTURE_H
#define FRAMESTRUCTURE_H

//#include "gridsquare.h" // WRONG -P
#include <timelinegrid.h>

// Frame data
typedef struct
{
    unsigned long ID = 0;         // Unique ID of frame. Static once generated.
    unsigned int duration;   // Frame Duration in MS

    //GridSquare **squareData;  //Frame data    WRONG -P
    //There will only ever be one GridSquare object, for the grid.
    //Each FrameData will however have its own TimelineGrid object, since the timeline will have more than one item

    //TimelineGrid **squareData  = new TimelineGrid*[V_GLOBAL.G_ROW];
    TimelineGrid **squareData  = new TimelineGrid*[20]; //always 20? fix later -P

} t_FrameData;

#endif // FRAMESTRUCTURE_H
