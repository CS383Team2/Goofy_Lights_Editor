#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "FrameList.h"
#include <QString>

class FileOperations
{
public:
    /* These two do NOT use the *.tan file format */
    /* Save to a file */
    static int SaveToFile(FrameList frameList, QString fileName);
    /* Load from a file */
    static FrameList LoadFromFile(QString fileName);

    /* These two DO use the *.tan file format
     * Neither of these are currently implemented
     */
    /* Export the current project as a *.tan file */
    static int ExportToFile(FrameList frameList);
    /* Import a *.tan file and add in the bufferspace */
    static FrameList ImportFromFile();
};

#endif // FILEOPERATIONS_H
