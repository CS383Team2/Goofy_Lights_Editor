
#include "FrameManipulation.h"
#include <iostream>

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
// Frame must be declared and rgb_data array must already be allocated
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/9
int copyFrame(t_FrameData &copyFrame, t_FrameData origFrame)
{
    // Error checking
    if (origFrame.data == NULL)
        return ERROR;

    // Row/col data
    unsigned short row = origFrame.r;
    unsigned short col = origFrame.c;
    int i, j; // loop control

    //Fill rgb_data with data from FrameData
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            copyFrame.data[i][j] = origFrame.data[i][j];
        }
    }

    return SUCSSESFUL;
}

// translates from by a given direction
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/7
int translateFrame(t_FrameData d, int direction)
{
    int i = 0; //counters
    int j = 0;
    t_RGB *temp; //Temp variable for row that is pushed out of the frame
    t_RGB emptyRGB;
    emptyRGB.B = 0;
    emptyRGB.G = 0;
    emptyRGB.R = 0;

    //Condition for up, up left, and up right. Uses recursion for left and right translation
    if(direction == D_UP || direction == D_UP_L || direction == D_UP_R){
        temp = d.data[0];
        for(i = 0; i < d.r-1; i++){
            d.data[i] = d.data[i+1];
        }
        d.data[i] = temp;
        for(int j = 0; j < d.c; j++){
            d.data[i][j] = emptyRGB;

        }
        if(direction == D_UP_L)
            translateFrame(d, D_LEFT);
        if(direction == D_UP_R)
            translateFrame(d, D_RIGHT);

    }
    //Condition for down, down left, and down right. Uses recursion for left and right translation
    if(direction == D_DWN || direction == D_DWN_L || direction == D_DWN_R){
        temp = d.data[d.r-1];
        for(i = d.r-1; i > 0; i--){
            d.data[i] = d.data[i-1];
        }
        d.data[i] = temp;
        for(j = 0; j < d.c; j++){
            d.data[i][j] = emptyRGB;
        }
        if(direction == D_DWN_L)
            translateFrame(d, D_LEFT);
        if(direction == D_DWN_R)
            translateFrame(d, D_RIGHT);
    }
    //Condition for left transition
    if(direction == D_LEFT){
        for(i = 0; i < d.r; i++){
            for (j = 0; j < d.c-1; j++){
                d.data[i][j] = d.data[i][j+1];
            }
        }
        for(i = 0; i < d.r; i++){
            d.data[i][j] = emptyRGB;
        }
     }
    //Condition for right transition
    if(direction == D_RIGHT){
        for(i = 0; i < d.r; i++){
            for (j = d.c-1; j > 0; j--){
                d.data[i][j] = d.data[i][j-1];
            }
        }
        for(i = 0; i < d.r; i++){
            d.data[i][j] = emptyRGB;
        }
     }

    return SUCSSESFUL;
}

// Fills given frame with color
//https://github.com/CS383Team2/Goofy_Lights_Editor/issues/6
int fillFrame(t_FrameData &d, t_RGB rgb_fill)
{
    // Dereference
    unsigned short row = d.r;
    unsigned short col = d.c;
    int i, j; // loop control

    // Error checking
    if (d.data == NULL)
        return ERROR;

    //Fill data
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
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
