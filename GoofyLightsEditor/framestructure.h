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
    unsigned long ID;         // Unique ID of frame. Static once generated.
    unsigned int durration;   // Frame Duration in MS
    t_RGB** data;  //Frame data
} t_FrameData;

#endif // FRAMESTRUCTURE_H
