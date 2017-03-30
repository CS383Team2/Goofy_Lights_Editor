
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

int delete_RGB(t_RGB** arr, int r, int c)
{
    if (arr == nullptr)
        return ERROR;

    //Reference: http://www.cplusplus.com/forum/beginner/38226/
    for(int i = 0; i < r; ++i)
        delete [] arr[i];   // delete data arrays
    delete [] arr;          // delete pointer array
    arr = nullptr;          // null the pointer
    return SUCSSESFUL;
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

int fillFrame2(t_FrameData &d, unsigned short r, unsigned short g, unsigned short b)
{
    t_RGB rgb;
    rgb.R = r;
    rgb.G = g;
    rgb.B = b;

    // error check if over bounds for type short
    if (r > 255 || g > 255 || b > 255)
        return ERROR;

    return fillFrame(d, rgb);
}
