#include "player.h"
#include "ui_player.h"

Player::Player(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);

    //grab the linked list
}

Player::~Player()
{
    delete ui;
}

void Player::on_Btn_close_clicked()
{
    close();
}

void Player::on_pushButton_clicked()
{
    //drawGrid
    //grab next frame
    //sleep / loop
}
