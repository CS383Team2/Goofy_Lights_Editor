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
#include <QFileInfo>
#include <QtDebug>
#include <QMessageBox>
#include <QTime>
#include <iostream>

#define VERSION .3

/* Save the project to a file. There is no predefined file format for this */
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
                    stream << frameData.squareData[i][j].square_RGB.red() << " "
                           << frameData.squareData[i][j].square_RGB.green() << " "
                           << frameData.squareData[i][j].square_RGB.blue() << " ";
                }
                stream << endl;
            }
            elapsedTime = elapsedTime.addMSecs(frameData.duration);
        }while(frameList.AdvanceList());
        file.close();
        return 1;
    }
    else
        return 0;
}

/* Load a project from a file. */
int FileOperations::LoadFromFile(QString fileName, FrameList * frameList){
    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0,"error",file.errorString());
        return -1;
    }
    QTextStream fileContents(&file);
    QString version = fileContents.readLine();

    QStringList currLineList = fileContents.readLine().split(" ");
    while(currLineList.count() > 3){
        currLineList = fileContents.readLine().split(" ");
    }
    /* Get the frame size from the file */
    QStringList frameInfo = currLineList;

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

        //std::cout << frameData.ID << "\n";

        TimelineGrid ** data = create_RGB(row, col);

        for(int i = 0; i < row; i++){
            QString line = fileContents.readLine();
            QStringList rowValues = line.split(" ", QString::SkipEmptyParts);
            // qDebug() << rowValues << endl;
            int j = 0;
            for(int k = 0; k < rowValues.size(); k += 3){
                data[i][j].square_RGB.setRed(rowValues[k].toShort());
                data[i][j].square_RGB.setGreen(rowValues[k + 1].toShort());
                data[i][j].square_RGB.setBlue(rowValues[k + 2].toShort());
                j++;
            }
        }
        frameData.squareData      = data;
        QString timeStr     = fileContents.readLine();
        QTime time;
        time                = QTime::fromString(timeStr, "mm:ss.zzz");
        nextTime            = time;
        frameData.durration = currTime.msecsTo(nextTime);
        frameData.ID        = currentElement;
        tmpFrameList.AddTail(frameData);
        // std::cout << "Current FrameList" << std::endl;
        // tmpFrameList.PrintNode();
        // std::cout << currentElement << std::endl;
        currentElement++;
    }
    file.close();
    (*frameList) = tmpFrameList;
    //std::cout << "Function Print\n";
    //tmpFrameList.PrintNode();
    (*frameList).PrintNode();
    return 1;
}
