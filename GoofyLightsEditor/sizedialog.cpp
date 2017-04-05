#include "sizedialog.h"
#include "ui_sizedialog.h"
#include <globals.h> //G_ROW and G_COL
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
    G_ROW=ui->sbox_Row->value();
}

void SizeDialog::on_sbox_Col_editingFinished()
{
    G_COL=ui->sbox_Col->value();
}

void SizeDialog::on_btnBox_OkClose_accepted()
{
    G_COL=ui->sbox_Col->value();
    G_ROW=ui->sbox_Row->value(); //redundant redundant, shush -P

    double max = 0;

    if(G_COL > G_ROW)
        max = G_COL;
    else
        max = G_ROW;

    //MAIN WINDOW TOO BIG, gonna take the scaling down to 85% -P
    G_SCALE = ((20.0 / max) * 0.85); //scaled based on a max size of 20x20 -P
}

void SizeDialog::on_btnBox_OkClose_rejected()
{
    exit(0); //Don't run the main window -P
}

void SizeDialog::on_btn_Browse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open a Goofy File!"), QDir::homePath(), tr("Only .tan Files (*.tan)")); //browse filename -P
    //fun stuff -P
    //filename variable now contains the file we want, woohoo
    //do stuff with this later -P
}
