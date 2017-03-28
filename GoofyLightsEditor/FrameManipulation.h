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


// Prototypes

// creates a RGB Array and returns a pointer to it.
t_RGB** create_RGB(int r, int c);


// Takes origional frame and returnes a new copy of it
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/9
t_FrameData copyFrame(t_FrameData FrameData);

// translates from by a given direction
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/7
int translateFrame(t_FrameData d, int direction);

// Fills given frame with color
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/6
int fillFrame(t_FrameData d, t_RGB rgb);
int fillFrame2(t_FrameData d, short r, short g, short b);

#endif // FRAMEMANIPULATION_H
