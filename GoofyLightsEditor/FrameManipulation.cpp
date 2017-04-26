
#include "FrameManipulation.h"
#include <iostream>
#include "globals.h"

// Function creates a 2d memory element of the RGB struct then passes back the pointer to it.
TimelineGrid** create_RGB(int r, int c)
{
    TimelineGrid** arr = new TimelineGrid*[r];
    for(int i = 0; i < r; ++i)
        arr[i] = new TimelineGrid[c];
    return arr;
}

TimelineGrid** create_RGB(int r, int c, int frameNumber)
{
    TimelineGrid** arr = new TimelineGrid*[r];
    for(int i = 0; i < r; ++i) {
        arr[i] = new TimelineGrid[c];
        for(int j=0; j<c; j++) {
            arr[i][j].timelineFrameNumber = frameNumber; //apply the frame number to every timelinesquare lol -P
        }
    }
    return arr;
}


// Takes origional frame and returnes a new copy of it
// Frame must be declared and rgb_data array must already be allocated
int copyFrame(t_FrameData *copyFrame, t_FrameData *origFrame)
{
    // Error checking
    if ((*origFrame).squareData == NULL)
        return RTN_ERROR;

    //Fill rgb_data with data from FrameData
    for (int i = 0; i < V_GLOBAL.G_ROW; i++) {
        for (int j = 0; j < V_GLOBAL.G_COL; j++) {
            (*copyFrame).squareData[i][j].square_RGB = (*origFrame).squareData[i][j].square_RGB;
        }
    }

    //copy duration
    copyFrame->duration = origFrame->duration;

    return RTN_SUCCESSFUL;
}

// translates from by a given direction
int translateFrame(t_FrameData *d, int direction)
{
    int i = 0; //counters
    int j = 0;
    TimelineGrid *temp; //Temp variable for row that is pushed out of the frame


    //Condition for up, up left, and up right. Uses recursion for left and right translation
    if(direction == D_UP || direction == D_UP_L || direction == D_UP_R){
        temp = d->squareData[0];
        for(i = 0; i < V_GLOBAL.G_ROW-1; i++){
            d->squareData[i] = d->squareData[i+1];
        }
        d->squareData[i] = temp;
        for(int j = 0; j < V_GLOBAL.G_COL; j++){
            d->squareData[i][j].square_RGB = Qt::black;

        }
        if(direction == D_UP_L)
            translateFrame(d, D_LEFT);
        if(direction == D_UP_R)
            translateFrame(d, D_RIGHT);

    }
    //Condition for down, down left, and down right. Uses recursion for left and right translation
    if(direction == D_DWN || direction == D_DWN_L || direction == D_DWN_R){
        temp = d->squareData[V_GLOBAL.G_ROW-1];
        for(i = V_GLOBAL.G_ROW-1; i > 0; i--){
            d->squareData[i] = d->squareData[i-1];
        }
        d->squareData[i] = temp;
        for(j = 0; j < V_GLOBAL.G_COL; j++){
            d->squareData[i][j].square_RGB = Qt::black;
        }
        if(direction == D_DWN_L)
            translateFrame(d, D_LEFT);
        if(direction == D_DWN_R)
            translateFrame(d, D_RIGHT);
    }
    //Condition for left transition
    if(direction == D_LEFT){
        for(i = 0; i < V_GLOBAL.G_ROW; i++){
            for (j = 0; j < V_GLOBAL.G_COL-1; j++){
                d->squareData[i][j].square_RGB = d->squareData[i][j+1].square_RGB;
            }
        }
        for(i = 0; i < V_GLOBAL.G_ROW; i++){
            d->squareData[i][j].square_RGB = Qt::black;
        }
     }
    //Condition for right transition
    if(direction == D_RIGHT){
        for(i = 0; i < V_GLOBAL.G_ROW; i++){
            for (j = V_GLOBAL.G_COL-1; j > 0; j--){
                d->squareData[i][j].square_RGB = d->squareData[i][j-1].square_RGB;
            }
        }
        for(i = 0; i < V_GLOBAL.G_ROW; i++){
            d->squareData[i][j].square_RGB = Qt::black;
        }
     }

    return RTN_SUCCESSFUL;
}

// Fills given frame with color. This function is broken and needs work.
int fillFrame(t_FrameData *d, QColor rgb_fill)
{
    int i, j; // loop control

    // Error checking
    if (d->squareData == NULL)
        return RTN_ERROR;

    //Fill data
    for (i = 0; i < V_GLOBAL.G_ROW; i++) {
        for (j = 0; j < V_GLOBAL.G_COL; j++) {
            d->squareData[i][j].square_RGB = rgb_fill;

        }
    }

    return RTN_SUCCESSFUL;
}
//This also needs some work.
int fillFrame2(t_FrameData *d, int r, int g, int b)
{
    QColor rgb;
    rgb.setRgb(r,g,b,255);

    // Error check if over bounds for type short
    if (r > 255 || g > 255 || b > 255)
        return RTN_ERROR;

    return fillFrame(d, rgb);
}
