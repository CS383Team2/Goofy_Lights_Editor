#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "FrameList.h"
#include <QString>

class FileOperations
{
public:
    /* Save to a file */
    static int SaveToFile(QString fileName, FrameList frameList);
    /* Load from a file */
    static int LoadFromFile(QString fileName, FrameList * frameList);
};

#endif // FILEOPERATIONS_H
