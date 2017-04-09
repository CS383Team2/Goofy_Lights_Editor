#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "FrameList.h"
#include <QString>

class FileOperations
{
public:
    /* Save to a file */
    static int SaveToFile(FrameList frameList, QString fileName);
    /* Load from a file */
    static int LoadFromFile(QString fileName, FrameList * frameList);
};

#endif // FILEOPERATIONS_H
