#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "FrameList.h"
#include <QString>

class fileoperations
{
public:
    /* These two do NOT use the *.tan file format */
    /* Save to a file */
    static int saveToFile(FrameList frameList, QString fileName);
    /* Load from a file */
    FrameList * loadFromFile(QString fileName);

    /* These two DO use the *.tan file format
     * Neither of these are currently implemented
     */
    /* Export the current project as a *.tan file */
    int exportToFile(FrameList frameList);
    /* Import a *.tan file and add in the bufferspace */
    FrameList * importFromFile();
};

#endif // FILEOPERATIONS_H
