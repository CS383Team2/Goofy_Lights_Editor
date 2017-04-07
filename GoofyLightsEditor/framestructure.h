#ifndef FRAMESTRUCTURE_H
#define FRAMESTRUCTURE_H

#include "gridsquare.h"

// Frame data
typedef struct
{
    unsigned long ID;         // Unique ID of frame. Static once generated.
    unsigned int duration;   // Frame Duration in MS
    GridSquare **squareData;  //Frame data
} t_FrameData;

#endif // FRAMESTRUCTURE_H
