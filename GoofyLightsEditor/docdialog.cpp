#include "docdialog.h"
#include "ui_docdialog.h"

docdialog::docdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::docdialog)
{
    ui->setupUi(this);
}

docdialog::~docdialog()
{
    delete ui;
}
