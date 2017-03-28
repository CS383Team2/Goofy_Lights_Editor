/* Handle the file operations
 * load/save json or xml for project
 * Import export .tan for production
 */

#include "fileoperations.h"
#include "FrameList.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QApplication>
#include <QWidget>
#include <QString>
#include <QObject>

int fileoperations::saveToFile(FrameList frameList, QString fileName){
    QFile file; /* Load the file and write to it */
    file.setFileName(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file); /* Stream that writes to the file */

        stream << frameList.GetRowCount() << "," << frameList.GetColCount() << endl;
        stream << frameList.Size() << endl << endl;

        do{
            t_FrameData frameData = frameList.FirstNode();

            for(int i = 0; i < frameList.GetRowCount(); i++){
                for(int j = 0; j < frameList.GetColCount(); j++){
                    stream << frameData.data[i][j].R << ","
                           << frameData.data[i][j].G << ","
                           << frameData.data[i][j].B << ";";
                }
                stream << endl;
            }
        }while(frameList.AdvanceList());
        return 1;
    }
    else
        return 0;
}

