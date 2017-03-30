
#include "FrameManipulation.h"


// Function creates a 2d memory element of the RGB struct then passes back the pointer to it.
// source http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
t_RGB** create_RGB(int r, int c)
{
    t_RGB** arr = new t_RGB*[r];
    for(int i = 0; i < r; ++i)
        arr[i] = new t_RGB[c];
    return arr;
}


// creates a RGB Array and returns a pointer to it.
t_RGB** create_RGB(int r, int c);


// Takes origional frame and returnes a new copy of it
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/9
t_FrameData copyFrame(t_FrameData FrameData)
{
    t_FrameData NewFrame;
    //Black magic
    return NewFrame;
}

// translates from by a given direction
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/7
int translateFrame(t_FrameData d, int direction)
{
    //Black magic
    return SUCSSESFUL;
}

// Fills given frame with color
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/6
int fillFrame(t_FrameData &d, t_RGB rgb_fill)
{
    // Dereference
    unsigned short r = d.r;
    unsigned short c = d.c;
    int i, j; // loop control

    // Error checking
    if (d.data == nullptr)
        return ERROR;

    //Fill data
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            d.data[i][j] = rgb_fill;
        }
    }

    return SUCSSESFUL;
}

int fillFrame2(t_FrameData &d, short r, short g, short b)
{
    t_RGB rgb;
    rgb.R = r;
    rgb.G = g;
    rgb.B = b;

    return fillFrame(d, rgb);
}
