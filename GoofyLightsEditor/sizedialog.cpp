#include "sizedialog.h"
#include "ui_sizedialog.h"
#include <globals.h> //G_ROW and G_COL
#include <globals.h>
#include <mainwindow.h>


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

void SizeDialog::on_buttonBox_accepted()
{
    G_COL=ui->spinBox_2->value();
    G_ROW=ui->spinBox->value(); //redundant redundant, shush -P

    //QWidget::repaint(); //DRAW THE NEW GRID -P
    //set = true;
    //MainWindow(this);
}
