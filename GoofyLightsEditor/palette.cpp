#include "palette.h"
#include "palettesquare.h"
#include "gridsquare.h"
#include <globals.h>
#include <mainwindow.h>

Palette::Palette()
{
    firstColor = NULL;
    lastColor = firstColor;
    numColors = 0;
}

Palette::~Palette()
{
    PalettePtr p = firstColor;
    PalettePtr n;

    while (p != NULL)
    {
       n = p;
       p = p->next;
       delete n;
    }
}

void Palette::insertColor(QColor newColor)
{
    if ((checkPalette(newColor)) && newGridColor)
    {
        PalettePtr P, temp;
        P = new node;
        P->PaletteColor = newColor;
        P->next = NULL;
        numColors++;
        if (firstColor == NULL)
        {
            firstColor = P;
            lastColor = firstColor;
        }
        else
        {
            lastColor->next = P;
            temp = lastColor;
            lastColor = temp->next;
        }
    }
    if(numColors == 9)
        deleteColor();
}

void Palette::deleteColor()
{
    PalettePtr P;
    if( firstColor != NULL )
    {
        P = firstColor;
        firstColor = firstColor->next;
        delete P;
        numColors--;
    }
}

bool Palette::checkPalette(QColor testColor)
{
    PalettePtr n;
    n = firstColor;
    for (int x = 0; x < numColors; x++)
    {
        if(n->PaletteColor == testColor)
            return false;
        n = n->next;
    }
    return true;
}

int Palette::getNumColors()
{
    return numColors;
}

QColor Palette::getColor(int num)
{
    PalettePtr n;
    n = firstColor;
    for (int x = 0; x < num; x++)
    {
        n = n->next;
    }
    return n->PaletteColor;
}
