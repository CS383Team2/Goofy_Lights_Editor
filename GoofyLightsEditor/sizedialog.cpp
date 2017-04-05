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

void SizeDialog::on_spinBox_editingFinished()
{
    G_ROW=ui->spinBox->value();
}

void SizeDialog::on_spinBox_2_editingFinished()
{
    G_COL=ui->spinBox_2->value();
}

void SizeDialog::on_btnBox_OkClose_accepted()
{
    G_COL=ui->spinBox_2->value();
    G_ROW=ui->spinBox->value(); //redundant redundant, shush -P
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
