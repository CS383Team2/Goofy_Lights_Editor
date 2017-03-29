/* Handle the file operations
 * load/save json or xml for project
 * Import export .tan for production
 */

#include "FileOperations.h"
#include "FrameManipulation.h"
#include "FrameList.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QApplication>
#include <QWidget>
#include <QString>
#include <QObject>
#include <QtDebug>
#include <QMessageBox>
#include <iostream>

/* Save the project to a file. There is no predefined file format for this
 * I would like to convert it to print a JSON or XML file in the future.
 */
int FileOperations::SaveToFile(FrameList frameList, QString fileName){
    QFile file; /* Load the file and write to it */
    file.setFileName(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file); /* Stream that writes to the file */

        stream << frameList.GetRowCount() << "," << frameList.GetColCount() << endl;
        stream << frameList.Size() << endl;

        /* If the frameList is empty */
        if(frameList.Size() == 0)
            return 0;

        do{
            qDebug() << "We got to the do..while";
            qDebug() << frameList.Size();
            t_FrameData frameData = frameList.FirstNode();

            stream << frameData.ID << endl;
            stream << frameData.durration << endl;

            for(int i = 0; i < frameList.GetRowCount(); i++){
                for(int j = 0; j < frameList.GetColCount(); j++){
                    stream << frameData.data[i][j].R << ","
                           << frameData.data[i][j].G << ","
                           << frameData.data[i][j].B << ";";
                }
                stream << endl;
            }
        }while(frameList.AdvanceList());
        file.close();
        return 1;
    }
    else
        return 0;
}

/* Load a project from a file.
 * Currently is looking for a file in the same format as the above save file
 */
FrameList FileOperations::LoadFromFile(QString fileName){
    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0,"error",file.errorString());
        //return FrameList(0,0); // Return a frame list with size 0,0
    }
    QTextStream fileContents(&file);
    /* Get the frame size from the file */
    QStringList frameSize = fileContents.readLine().split(",");

    int row = frameSize[0].toInt();
    int col = frameSize[1].toInt();

    /* Initialize the frame list */
    FrameList frameList = FrameList(row, col);

    int numElements = fileContents.readLine().toInt(); // Nothing is currently done with this.

    int currentElement = 0;
    while(!fileContents.atEnd() && currentElement < numElements){
        t_FrameData frameData;
        frameData.ID        = fileContents.readLine().toULong();
        frameData.durration = fileContents.readLine().toULong();

        //std::cout << frameData.ID << "\n";

        t_RGB ** data = create_RGB(row, col);

        for(int i = 0; i < row; i++){
            QString line = fileContents.readLine();
            QRegExp rx("\\,|\\;");
            QStringList rowValues = line.split(rx, QString::SkipEmptyParts);
            // qDebug() << rowValues << endl;
            int j = 0;
            for(int k = 0; k < rowValues.size(); k += 3){
                data[i][j].R = rowValues[k].toShort();
                data[i][j].G = rowValues[k + 1].toShort();
                data[i][j].B = rowValues[k + 2].toShort();
                j++;
            }
        }
        frameData.data = data;
        frameList.AddNode(frameData);
        // frameList.PrintNode();
        currentElement++;
    }
    file.close();
    //std::cout << "Function Print\n";
    //frameList.PrintNode();
    return frameList;
}

