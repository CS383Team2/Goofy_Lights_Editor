#ifndef FRAMEMANIPULATION_H
#define FRAMEMANIPULATION_H

#include "framestructure.h"

// Directions used in translate frame function
#define D_UP        1
#define D_DWN       2
#define D_LEFT      3
#define D_RIGHT     4
#define D_UP_L      5
#define D_UP_R      6
#define D_DWN_L     7
#define D_DWN_R     8

// Return codes
#define RTN_SUCCESSFUL  0
#define RTN_ERROR       1


// Prototypes

//creates a RGB Array and returns a pointer to it.
TimelineGrid** create_RGB(int r, int c);

//creates a RGB Array, returns a pointer to it, and assigns a frame number to the data
TimelineGrid** create_RGB(int r, int c, int frameNumber);

//Takes origional frame and returnes a new copy of it
int copyFrame(t_FrameData *copyFrame, t_FrameData *origFrame);

//Translate a frame to the given direction. For up and down swaps pointer rows around to
//move data. For left and right function has to move every single data point in the array in the
//specified direction.
int translateFrame(t_FrameData *d, int direction);

//Fills given frame with color
int fillFrame(t_FrameData *d, QColor rgb_fill);

//Takes in rgb values and assigns them to a QColor variable that is passed into
//fill frame along with the FrameData
int fillFrame2(t_FrameData *d, int r, int g, int b);

#endif // FRAMEMANIPULATION_H
