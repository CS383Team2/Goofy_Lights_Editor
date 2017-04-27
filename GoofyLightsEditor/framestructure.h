#ifndef FRAMESTRUCTURE_H
#define FRAMESTRUCTURE_H

#include <timelinegrid.h>

// Frame data
typedef struct
{
    int ID = 0;				// Unique ID of frame. Static once generated.
    int Position = 0;			// Each Frames position in the time line, starting with (Head Nodes Position = 0)
    double duration;	   			// Frame Duration in MS

    TimelineGrid **squareData  = new TimelineGrid*[20]; //always 20? fix later -P

} t_FrameData;

#endif // FRAMESTRUCTURE_H
