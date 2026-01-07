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

void GamePanel::CropImage(QPixmap &pix, int x, int y, Card &c)
{
    QPixmap sub = pix.copy(x, y, card_size_.width(), card_size_.height());
    CardPanel* panel = new CardPanel(this);
    panel->SetImage(sub, card_back_image_);
    card_map_.insert(c, panel);
    panel->hide();
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

    connect(game_ctl_, &GameControl::PlayerStatusChanged, this, &GamePanel::OnPlayerStatusChanged);
}

void GamePanel::GameStatusProcess(GameControl::GameStatus status)
{
    switch(status)
    {
        case GameControl::GameStatus::DISPATCH_CARD:
        {
            StartDispatchCard();
            break;
        }
        case GameControl::GameStatus::CALLING_LORD:
        {
            for(int i = 0; i < last_3_cards_.size(); i++)
            {
                last_3_cards_[i]->hide();
            }
            game_ctl_->StartLordCard();
            break;
        }
        default:
            break;
    }
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

void GamePanel::OnPlayerStatusChanged(Player *player, GameControl::PlayerStatus status)
{
    switch(status)
    {
        case GameControl::PlayerStatus::THINKING_FOR_CALL_LORD:
        {
            if(player == game_ctl_->GetUserPlayer())
            {
                ui->button_group_->SelectPanel(ButtonGroup::Panel::CALL_LORD);
            }
            break;
        }
        default :
            break;
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
    for(int i = 0, suit = Card::CardSuit::SUIT_BEGIN + 1; suit < Card::CardSuit::SUIT_END; ++suit, ++i)
    {
        for(int j = 0, pt = Card::CardPoint::CARD_BEGIN + 1; pt < Card::CardPoint::CARD_SJ; ++pt, ++j)
        {
            Card card((Card::CardPoint)pt, (Card::CardSuit)suit);
            /// 裁剪图片
            CropImage(pixmap, j * card_size_.width(), i * card_size_.height(), card);
        }
    }

    /// 小王
    Card card_small_joker(Card::CardPoint::CARD_SJ, Card::CardSuit::SUIT_BEGIN);
    CropImage(pixmap, 0, 4 * card_size_.height(), card_small_joker);
    /// 大王
    Card card_big_joker(Card::CardPoint::CARD_BJ, Card::CardSuit::SUIT_BEGIN);
    CropImage(pixmap, card_size_.width(), 4 * card_size_.height(), card_big_joker);
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
    Cards cards = player->GetCards();           ///< 获取玩家所有卡牌
    QVector<Card> list = cards.ToCardList();

    /// 玩家扑克牌展示区
    int card_space = 20;                        ///< 玩家扑克牌展示间隔
    QRect cards_rect = context_map_[player].card_rect_;

    for(int i = 0; i < list.size(); i++)
    {
        CardPanel* temp_card = card_map_[list.at(i)];
        temp_card->SetFrontSide(context_map_[player].is_front_);
        /// 水平 or 垂直显示
        QPoint temp_pos;

        int left_x = cards_rect.left();
        int top_y = cards_rect.top();
        if(context_map_[player].align_ == CardAlign::HORIZONTAL)
        {
            /// 让卡牌在中间开始显示
            left_x += (cards_rect.width() - (list.size() - 1) * card_space - temp_card->width()) / 2;
            left_x += card_space * i;           ///< 第 i 个卡牌显示位置
            /// 让卡牌在中间显示
            top_y += (cards_rect.height() - temp_card->height()) / 2;
        }
        else
        {
            left_x += (cards_rect.width() - temp_card->width()) / 2;
            top_y += (cards_rect.height() - (list.size() - 1) * card_space - temp_card->height()) / 2;
            top_y += i * card_space;
        }

        temp_pos = QPoint(left_x, top_y);
        temp_card->move(temp_pos);
        temp_card->show();
        temp_card->raise();
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
            /// 终止定时器
            timer_->stop();
            /// 切换游戏状态
            GameStatusProcess(GameControl::GameStatus::CALLING_LORD);
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
        context.is_front_ = i == index ? true : false;
        context_map_.insert(player_list_.at(i), context);
    }
}

void GamePanel::InitButtonsGroup()
{
    ui->button_group_->InitButtons();
    ui->button_group_->SelectPanel(ButtonGroup::Panel::START);
    connect(ui->button_group_, &ButtonGroup::StartGame, this, [=](){
        GameStatusProcess(GameControl::GameStatus::DISPATCH_CARD);
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
