#ifndef FRAMESTRUCTURE_H
#define FRAMESTRUCTURE_H

// RGB
typedef struct
{
    short R;    // Red
    short G;    // Green
    short B;    // Blue
} t_RGB;

// Frame data
typedef struct
{
    long ID;         // Unique ID of frame. Static once generated.
    int durration;   // Frame Duration in MS
    // Where do we get the R C from at this point?
    //RGB data[??][??]  //Frame data
} t_FrameData;

#endif // FRAMESTRUCTURE_H
