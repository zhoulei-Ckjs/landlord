#include "game_pannel.h"
#include "./ui_game_pannel.h"

game_pannel::game_pannel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::game_pannel)
{
    ui->setupUi(this);
}

game_pannel::~game_pannel()
{
    delete ui;
}
