#include "game_panel.h"
#include "./ui_game_panel.h"

GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);
}

GamePanel::~GamePanel()
{
    delete ui;
}
