#include "button_group.h"
#include "ui_button_group.h"

ButtonGroup::ButtonGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ButtonGroup)
{
    ui->setupUi(this);
}

ButtonGroup::~ButtonGroup()
{
    delete ui;
}

void ButtonGroup::InitButtons()
{
    /// 设置开始游戏图片
    ui->start_->SetImage(":/res/img/button_group/start/start.png", ":/res/img/button_group/start/hover.png", ":/res/img/button_group/start/pressed.png");
    /// 设置出牌按钮图片
    ui->play_card_->SetImage(":/res/img/button_group/play_card/normal.png", ":/res/img/button_group/play_card/hover.png", ":/res/img/button_group/play_card/pressed.png");
}

void ButtonGroup::SelectPanel()
{
    ui->stacked_widget_->setCurrentIndex(1);
}
