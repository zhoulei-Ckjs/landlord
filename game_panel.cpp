#include "game_panel.h"
#include "./ui_game_panel.h"
#include "card.h"

#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>

GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    /// 背景图
    int background_image_index = QRandomGenerator::global()->bounded(10);   ///< 生成[0,10)的随机数。
    QString background_image_path = QString(":/res/img/background/background-%1.png").arg(background_image_index + 1);
    background_image_.load(background_image_path);

    /// 窗口的标题和大小
    this->setWindowTitle("欢乐斗地主");
    this->setFixedSize(1000, 650);      ///< 设置窗口的固定大小，使窗口不能拉伸

    /// 实例化游戏控制类对象
    GameControlInit();

    /// 更新玩家得分
    UpdatePlayerScore();

    /// 切割并存储图片
    InitCardMap();

    /// 初始化游戏中按钮组
    InitButtonsGroup();

    /// 初始化玩家在窗口中的上下文
    InitPlayerContext();

    /// 扑克牌场景初始化
    InitGameScene();

    /// 定时器实例化
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &GamePanel::OnDispatchCard);
}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::GameControlInit()
{
    game_ctl_ = new GameControl(this);
    game_ctl_->PlayerInit();

    Player* right_robot = game_ctl_->GetRightRobot();
    Player* user = game_ctl_->GetUserPlayer();
    Player* left_robot = game_ctl_->GetLeftRobot();

    /// 存储的顺序: 右侧机器人, 当前玩家, 左侧机器人
    player_list_ << right_robot << user << left_robot;
}

void GamePanel::InitGameScene()
{
    /// 发牌区不动的扑克牌
    base_card_ = new CardPanel(this);
    base_card_->SetImage(card_back_image_, card_back_image_);

    /// 发牌时移动的扑克牌
    move_card_ = new CardPanel(this);
    move_card_->SetImage(card_back_image_, card_back_image_);

    /// 最后的三张底牌
    for(int i = 0; i < 3; i++)
    {
        CardPanel* panel = new CardPanel(this);
        panel->SetImage(card_back_image_, card_back_image_);
        last_3_cards_.push_back(panel);
        panel->hide();
    }

    /// 发牌时刻中心卡牌的位置
    base_card_pos_ = QPoint((width() - card_size_.width()) / 2, height() / 2 - 100);
    base_card_->move(base_card_pos_);
    move_card_->move(base_card_pos_);   ///< 初始化位置

    /// 最后三张底牌
    int base = (width() - 3 * card_size_.width() - 2 * 10) / 2;
    for(int i = 0; i < 3; i++)
    {
        last_3_cards_[i]->move(base + (card_size_.width() + 10) * i, 20);
    }
}

void GamePanel::UpdatePlayerScore()
{
    ui->score_panel_->SetScores(0, 0, 0);
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

void GamePanel::StartDispatchCard()
{
    /// 重置所有玩家的卡牌数据
    game_ctl_->InitAllCards();

    /// 启动发牌定时器
    timer_->start(10);
}

void GamePanel::UpdatePlayerCards(Player *player)
{
    Cards cards = player->GetCards();       ///< 获取玩家所有卡牌
    static int pos_horizontal = 200;
    static int pos_vertical = 200;

    for(int i = 0; i < cards.CardsCount(); i++)
    {
        CardPanel* temp_card = new CardPanel(this);
        temp_card->SetImage(card_back_image_, card_back_image_);
        /// 水平 or 垂直显示
        QPoint temp_pos;
        if(context_map_[player].align_ == CardAlign::HORIZONTAL)
        {
            temp_pos = QPoint(pos_horizontal, 520);
            pos_horizontal += 10;
        }
        else
        {
            temp_pos = QPoint(0, pos_vertical);
            pos_vertical += 10;
        }

        temp_card->move(temp_pos);
        temp_card->show();
    }
}

void GamePanel::OnDispatchCard()
{
    static int cur_move_pos = 0;

    /// 当前玩家
    Player* cur_player = game_ctl_->GetCurrentPlayer();
    if(cur_move_pos >= 100)
    {
        /// 给玩家发一张牌
        Card card = game_ctl_->TakeOneCard();
        cur_player->StoreDispatchCard(card);
        Cards cards(card);
        DisposeCard(cur_player, cards);
        /// 切换玩家
        game_ctl_->SetCurrentPlayer(cur_player->GetNextPlayer());
        cur_move_pos = 0;

        /// 判断牌是否发完了
        if(game_ctl_->GetSurplusCards().CardsCount() == 3)
        {
            /// 中止定时器
            timer_->stop();
        }
    }
    CardMoveStep(cur_player, cur_move_pos);
    cur_move_pos += 15;
}

void GamePanel::CardMoveStep(Player* player, int cur_pos)
{
    /// 得到每个玩家的扑克牌展示区域
    QRect card_rect = context_map_[player].card_rect_;

    const int unit[]=
    {
        (card_rect.left() - base_card_pos_.x() - card_size_.width()) / 100,
        (card_rect.top() - base_card_pos_.y() - card_size_.height()) / 100,
        (base_card_pos_.x() - card_rect.right()) / 100
    };
    /// 每次窗口移动的时候每个玩家对应的牌的时时坐标位置
    const QPoint pos[] =
    {
        QPoint(base_card_pos_.x() + unit[0] * cur_pos, base_card_pos_.y()),
        QPoint(base_card_pos_.x(), base_card_pos_.y() + unit[1] * cur_pos),
        QPoint(base_card_pos_.x() - unit[2] * cur_pos, base_card_pos_.y())
    };

    /// 移动扑克牌
    int index = player_list_.indexOf(player);
    move_card_->move(pos[index]);
}

void GamePanel::InitPlayerContext()
{
    const QRect cards_rect[] =
    {
        /// x, y, width, height
        QRect(rect().right() - 190, 130, 100, height() - 200),  ///< 右侧机器人
        QRect(250, rect().bottom() - 120, width() - 500, 100),  ///< 玩家
        QRect(90, 130, 100, height() - 200)                     ///< 左侧机器人
    };
    int index = player_list_.indexOf(game_ctl_->GetCurrentPlayer());
    for(int i = 0; i < player_list_.size(); i++)
    {
        PlayerContext context;
        context.card_rect_ = cards_rect[i];
        context.align_= i == index ? CardAlign::HORIZONTAL : CardAlign::VERTICAL;
        context_map_.insert(player_list_.at(i), context);
    }
}

void GamePanel::InitButtonsGroup()
{
    ui->button_group_->InitButtons();
    ui->button_group_->SelectPanel(ButtonGroup::Panel::START);
    connect(ui->button_group_, &ButtonGroup::StartGame, this, [=](){
        StartDispatchCard();
    });
}

void GamePanel::DisposeCard(Player *player, const Cards &cards)
{
    UpdatePlayerCards(player);
}

void GamePanel::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    /// 绘制背景图片
    p.drawPixmap(rect(), background_image_);
}
