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
#include <QTime>
#include <iostream>

#define VERSION .3

/* Save the project to a file. There is no predefined file format for this
 * I would like to convert it to print a JSON or XML file in the future.
 */
int FileOperations::SaveToFile(FrameList frameList, QString fileName){
    QFile file; /* Load the file and write to it */
    QTime elapsedTime = QTime(0,0,0,0); // Time elapsed in milliseconds
    file.setFileName(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file); /* Stream that writes to the file */

        stream << VERSION << endl;
        stream << frameList.Size() << " "
               << frameList.GetRowCount() << " "
               << frameList.GetColCount() << endl;

        /* If the frameList is empty */
        if(frameList.Size() == 0)
            return 0;

        do{
            t_FrameData frameData = frameList.FirstNode();

            // stream << frameData.ID << endl;
            stream << elapsedTime.toString("mm:ss.zzz") << endl;

            for(int i = 0; i < frameList.GetRowCount(); i++){
                for(int j = 0; j < frameList.GetColCount(); j++){
                    stream << frameData.data[i][j].R << " "
                           << frameData.data[i][j].G << " "
                           << frameData.data[i][j].B << " ";
                }
                stream << endl;
            }
            elapsedTime = elapsedTime.addMSecs(frameData.durration);
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
int FileOperations::LoadFromFile(QString fileName, FrameList * frameList){
    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0,"error",file.errorString());
        //return FrameList(0,0); // Return a frame list with size 0,0
    }
    QTextStream fileContents(&file);
    QString version = fileContents.readLine();
    /* Get the frame size from the file */
    QStringList frameInfo = fileContents.readLine().split(" ");

    // qDebug() << frameInfo << endl;

    int numElements = frameInfo[0].toInt();
    int row         = frameInfo[1].toInt();
    int col         = frameInfo[2].toInt();

    /* Initialize the frame list */
    FrameList tmpFrameList = FrameList(row, col);

    int currentElement = 0;
    QString startTime = fileContents.readLine();
    QTime currTime = QTime::fromString(startTime, "mm:ss.zzz");
    QTime nextTime = QTime(0,0,0,0);
    while(!fileContents.atEnd() && currentElement < numElements){
        t_FrameData frameData;
        currTime = nextTime;
        frameData.ID        = currentElement;

        //std::cout << frameData.ID << "\n";

        t_RGB ** data = create_RGB(row, col);

        for(int i = 0; i < row; i++){
            QString line = fileContents.readLine();
            QStringList rowValues = line.split(" ", QString::SkipEmptyParts);
            // qDebug() << rowValues << endl;
            int j = 0;
            for(int k = 0; k < rowValues.size(); k += 3){
                data[i][j].R = rowValues[k].toShort();
                data[i][j].G = rowValues[k + 1].toShort();
                data[i][j].B = rowValues[k + 2].toShort();
                j++;
            }
        }
        frameData.data      = data;
        QString timeStr     = fileContents.readLine();
        QTime time;
        time                = QTime::fromString(timeStr, "hh:mm:ss.zzz");
        nextTime            = time;
        frameData.durration = currTime.msecsTo(nextTime);
        tmpFrameList.AddTail(frameData);
        // frameList.PrintNode();
        currentElement++;

    }
    file.close();
    *frameList = tmpFrameList;
    //std::cout << "Function Print\n";
    //frameList.PrintNode();
    //return frameList;
}
