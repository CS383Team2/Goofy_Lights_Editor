#include "docdialog.h"
#include "ui_docdialog.h"
#include <helpdialog.h>

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

void docdialog::on_pushButton_clicked()
{
    close(); //close this window on OK -P
}

void docdialog::on_pushButton_2_clicked()
{
    close();
    //pop the help dialog -P
    helpdialog dialog2;
    dialog2.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint); //You will NOT exit this window your way -P
    dialog2.setModal(true); //YOU SHALL NOT CLICK OUTSIDE OF THIS WINDOW -P
    dialog2.exec(); //execute pls -P
}
