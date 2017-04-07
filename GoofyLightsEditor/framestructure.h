#ifndef FRAMESTRUCTURE_H
#define FRAMESTRUCTURE_H

#include "gridsquare.h"

// RGB
typedef struct
{
    unsigned short R;    // Red
    unsigned short G;    // Green
    unsigned short B;    // Blue
} t_RGB;

// Frame data
typedef struct
{
    unsigned long ID;         // Unique ID of frame. Static once generated.
    unsigned int durration;   // Frame Duration in MS
    unsigned short r;   //Number of rows in frame
    unsigned short c;   //Number of columns in frame
    t_RGB **data;
    GridSquare **newdata;  //Frame data
} t_FrameData;

#endif // FRAMESTRUCTURE_H
