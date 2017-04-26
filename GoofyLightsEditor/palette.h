#ifndef PALETTE_H
#define PALETTE_H

#include "palettesquare.h"
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class Palette
{
private:
    struct node{
        QColor PaletteColor;
        struct node *next;
    };
    typedef struct node* PalettePtr;
    PalettePtr firstColor;
    PalettePtr lastColor;
    int size = 8;
    int numColors;
public:
    Palette();
    ~Palette();
    void insertColor(QColor newColor);
    void deleteColor();
    bool checkPalette(QColor testColor);
    int getNumColors();
    QColor getColor(int num);
};

#endif // PALETTE_H
