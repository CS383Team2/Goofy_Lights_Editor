#ifndef FRAMESTRUCTURE_H
#define FRAMESTRUCTURE_H

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
    unsigned int duration;   // Frame Duration in MS
    t_RGB** data;  //Frame data
} t_FrameData;

#endif // FRAMESTRUCTURE_H
