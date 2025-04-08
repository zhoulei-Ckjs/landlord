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
    ui->start_->SetImage(":/res/img/button_group/start.png");
}
