#ifndef FRAMEMANIPULATION_H
#define FRAMEMANIPULATION_H

#include "framestructure.h"

// Directions
#define D_UP        1
#define D_DWN       2
#define D_LEFT      3
#define D_RIGHT     4
#define D_UP_L      5
#define D_UP_R      6
#define D_DWN_L     7
#define D_DWN_R     8

// Return codes
#define SUCSSESFUL  0
#define ERROR       1


// Prototypes

// creates a RGB Array and returns a pointer to it.
TimelineGrid** create_RGB(int r, int c);

// Takes origional frame and returnes a new copy of it
int copyFrame(t_FrameData &copyFrame, t_FrameData origFrame);

// translates from by a given direction
int translateFrame(t_FrameData d, int direction);

// Fills given frame with color
int fillFrame(t_FrameData &d, QColor rgb_fill);
int fillFrame2(t_FrameData &d, int r, int g, int b);

#endif // FRAMEMANIPULATION_H
