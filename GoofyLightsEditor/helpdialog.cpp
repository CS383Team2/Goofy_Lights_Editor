#include "helpdialog.h"
#include "ui_helpdialog.h"
#include <docdialog.h>

helpdialog::helpdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpdialog)
{
    ui->setupUi(this);
}

helpdialog::~helpdialog()
{
    delete ui;
}

void helpdialog::on_pushButton_clicked()
{
    close(); //close on OK -P
}

void helpdialog::on_pushButton_2_clicked()
{
    close();
    //pop the doc dialog -P
    docdialog dialog2;
    dialog2.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint); //You will NOT exit this window your way -P
    dialog2.setModal(true); //YOU SHALL NOT CLICK OUTSIDE OF THIS WINDOW -P
    dialog2.exec(); //execute pls -P
}
