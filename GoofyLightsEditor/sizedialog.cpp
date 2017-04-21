#include "sizedialog.h"
#include "FileOperations.h"
#include "ui_sizedialog.h"
#include <globals.h> //V_GLOBAL.G_ROW and V_GLOBAL.G_COL
#include <mainwindow.h>
#include <QFileDialog> //file browser -P


SizeDialog::SizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeDialog)
{
    ui->setupUi(this);
}

SizeDialog::~SizeDialog()
{
    delete ui;
}

void SizeDialog::on_sbox_Row_editingFinished()
{
    V_GLOBAL.G_ROW=ui->sbox_Row->value();
}

void SizeDialog::on_sbox_Col_editingFinished()
{
    V_GLOBAL.G_COL=ui->sbox_Col->value();
}

void SizeDialog::on_btnBox_OkClose_accepted()
{
    V_GLOBAL.G_COL=ui->sbox_Col->value();
    V_GLOBAL.G_ROW=ui->sbox_Row->value(); //redundant redundant, shush -P
}

void SizeDialog::on_btnBox_OkClose_rejected()
{
    exit(0); //Don't run the main window -P
}

void SizeDialog::on_btn_Browse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Open a Goofy File!"),
                       QDir::homePath(), tr("Only .tan Files (*.tan)")); //browse filename -P

    FrameList frameList;
    FileOperations::LoadFromFile(fileName, &frameList);

    /* Copy data from frameList into global frame list
     * and update globals */`
    V_GLOBAL.G_FRAMELIST = new FrameList(frameList);
    (*(V_GLOBAL.G_FRAMELIST)).PrintNode();
    V_GLOBAL.G_CURRENTFRAME = 0;
    V_GLOBAL.G_FRAMECOUNT = (*(V_GLOBAL.G_FRAMELIST)).Size();
    V_GLOBAL.G_COL = (*(V_GLOBAL.G_FRAMELIST)).GetColCount();
    V_GLOBAL.G_ROW = (*(V_GLOBAL.G_FRAMELIST)).GetRowCount();

    // Update UI info
    ui->sbox_Col->setValue(V_GLOBAL.G_COL);
    ui->sbox_Row->setValue(V_GLOBAL.G_ROW);

    //fun stuff -P
    //filename variable now contains the file we want, woohoo
    //do stuff with this later -P
}
