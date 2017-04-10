
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


// Takes origional frame and returnes a new copy of it
// Frame must be declared and rgb_data array must already be allocated
int copyFrame(t_FrameData &copyFrame, t_FrameData origFrame)
{
    // Error checking
    if (origFrame.squareData == NULL)
        return ERROR;

    int i, j; // loop control

    //Fill rgb_data with data from FrameData
    for (i = 0; i < G_ROW; i++) {
        for (j = 0; j < G_COL; j++) {
            copyFrame.squareData[i][j].square_RGB = origFrame.squareData[i][j].square_RGB;
        }
    }

    return SUCSSESFUL;
}

// translates from by a given direction
int translateFrame(t_FrameData d, int direction)
{
    int i = 0; //counters
    int j = 0;
    TimelineGrid *temp; //Temp variable for row that is pushed out of the frame


    //Condition for up, up left, and up right. Uses recursion for left and right translation
    if(direction == D_UP || direction == D_UP_L || direction == D_UP_R){
        temp = d.squareData[0];
        for(i = 0; i < G_ROW-1; i++){
            d.squareData[i] = d.squareData[i+1];
        }
        d.squareData[i] = temp;
        for(int j = 0; j < G_COL; j++){
            d.squareData[i][j].square_RGB = Qt::black;

        }
        if(direction == D_UP_L)
            translateFrame(d, D_LEFT);
        if(direction == D_UP_R)
            translateFrame(d, D_RIGHT);

    }
    //Condition for down, down left, and down right. Uses recursion for left and right translation
    if(direction == D_DWN || direction == D_DWN_L || direction == D_DWN_R){
        temp = d.squareData[G_ROW-1];
        for(i = G_ROW-1; i > 0; i--){
            d.squareData[i] = d.squareData[i-1];
        }
        d.squareData[i] = temp;
        for(j = 0; j < G_COL; j++){
            d.squareData[i][j].square_RGB = Qt::black;
        }
        if(direction == D_DWN_L)
            translateFrame(d, D_LEFT);
        if(direction == D_DWN_R)
            translateFrame(d, D_RIGHT);
    }
    //Condition for left transition
    if(direction == D_LEFT){
        for(i = 0; i < G_ROW; i++){
            for (j = 0; j < G_COL-1; j++){
                d.squareData[i][j].square_RGB = d.squareData[i][j+1].square_RGB;
            }
        }
        for(i = 0; i < G_ROW; i++){
            d.squareData[i][j].square_RGB = Qt::black;
        }
     }
    //Condition for right transition
    if(direction == D_RIGHT){
        for(i = 0; i < G_ROW; i++){
            for (j = G_COL-1; j > 0; j--){
                d.squareData[i][j].square_RGB = d.squareData[i][j-1].square_RGB;
            }
        }
        for(i = 0; i < G_ROW; i++){
            d.squareData[i][j].square_RGB = Qt::black;
        }
     }

    return SUCSSESFUL;
}

// Fills given frame with color. This function is broken and needs work.
int fillFrame(t_FrameData &d, QColor rgb_fill)
{
    int i, j; // loop control

    // Error checking
    if (d.squareData == NULL)
        return ERROR;

    //Fill data
    for (i = 0; i < G_ROW; i++) {
        for (j = 0; j < G_COL; j++) {
            d.squareData[i][j].square_RGB.setRed(50/*rgb_fill.green()*/);
            d.squareData[i][j].square_RGB.setGreen(50/*rgb_fill.green()*/);
            d.squareData[i][j].square_RGB.setBlue(50/*rgb_fill.blue()*/);

        }
    }

    return SUCSSESFUL;
}
//This also needs some work.
int fillFrame2(t_FrameData &d, int r, int g, int b)
{
    QColor rgb;
    rgb.setRed(r);
    rgb.setGreen(g);
    rgb.setBlue(b);

    // error check if over bounds for type short
    if (r > 255 || g > 255 || b > 255)
        return ERROR;

    return fillFrame(d, rgb);
}
