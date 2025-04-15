#include "game_panel.h"
#include "./ui_game_panel.h"

#include <QPainter>
#include <QRandomGenerator>

GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    /// 初始化按钮组
    ui->button_group_->InitButtons();

    /// 切换栈窗口面板
    ui->button_group_->SelectPanel();

    /// 背景图
    int background_image_index = QRandomGenerator::global()->bounded(10);   ///< 生成[0,10)的随机数。
    QString background_image_path = QString(":/res/img/background/background-%1.png").arg(background_image_index + 1);
    background_image_.load(background_image_path);
}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    /// 绘制背景图片
    p.drawPixmap(rect(), background_image_);
}
