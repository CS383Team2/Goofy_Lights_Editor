#ifndef FRAMESTRUCTURE_H
#define FRAMESTRUCTURE_H

#include <timelinegrid.h>

//Structre containing the data for each frame. This includes frame position,
//duration, and the color for each square of the frame.
typedef struct
{
    int ID = 0;				// Unique ID of frame. Static once generated.
    int Position = 0;			// Each Frames position in the time line, starting with (Head Nodes Position = 0)
    double duration = 0.2;	   			// Frame Duration in MS

    TimelineGrid **squareData  = new TimelineGrid*[20]; //Always set to 20

} t_FrameData;

#endif // FRAMESTRUCTURE_H
