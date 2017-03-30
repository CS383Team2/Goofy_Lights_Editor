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
    unsigned short r;   //Number of rows in frame
    unsigned short c;   //Number of columns in frame
    t_RGB** data;  //Frame data
} t_FrameData;

#endif // FRAMESTRUCTURE_H
