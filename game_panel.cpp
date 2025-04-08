#include "game_panel.h"
#include "./ui_game_panel.h"

GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    /// 初始化按钮组
    ui->button_group_->InitButtons();
}

GamePanel::~GamePanel()
{
    delete ui;
}
