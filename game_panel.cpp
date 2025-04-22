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

    /// 窗口的标题和大小
    this->setWindowTitle("欢乐斗地主");
    this->setFixedSize(1000, 650);      ///< 设置窗口的固定大小，使窗口不能拉伸

    InitCardMap();

    /// 扑克牌场景初始化
    InitGameScene();
}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::InitGameScene()
{
    /// 发牌区不动的扑克牌
    base_card_ = new CardPanel(this);
    base_card_->SetImage(card_back_image_, card_back_image_);

    /// 最后的三张底牌
    for(int i = 0; i < 3; i++)
    {
        CardPanel* panel = new CardPanel(this);
        panel->SetImage(card_back_image_, card_back_image_);
        last_3_cards_.push_back(panel);
    }

    /// 发牌时刻中心卡牌的位置
    base_card_pos_ = QPoint((width() - card_size_.width()) / 2, height() / 2 - 100);
    base_card_->move(base_card_pos_);
    /// 最后三张底牌
    int base = (width() - 3 * card_size_.width() - 2 * 10) / 2;
    for(int i = 0; i < 3; i++)
    {
        last_3_cards_[i]->move(base + (card_size_.width() + 10) * i, 20);
    }
}

void GamePanel::InitCardMap()
{
    /// 加载大图
    QPixmap pixmap(":/res/img/card/card.png");

    /// 计算每张图片的大小
    card_size_.setWidth(pixmap.width() / 13);
    card_size_.setHeight(pixmap.height() / 5);

    /// 扑克牌背面图
    card_back_image_ = pixmap.copy(2 * card_size_.width(), 4 * card_size_.height(), card_size_.width(), card_size_.height());
}

void GamePanel::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    /// 绘制背景图片
    p.drawPixmap(rect(), background_image_);
}
