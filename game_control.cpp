#include "game_control.h"

#include <QDebug>

GameControl::GameControl(QObject *parent)
    : QObject{parent}
{}

void GameControl::PlayerInit()
{
    /// 对象初始化
    robot_left_ = new Robot("left robot", this);
    robot_right_ = new Robot("right robot", this);
    user_ = new UserPlayer("you", this);

    /// 出牌顺序
    user_->SetNextPlayer(robot_left_);
    robot_right_->SetNextPlayer(user_);
    robot_left_->SetNextPlayer(robot_right_);

    /// 指定当前玩家
    curr_player_ = user_;

    /// 处理玩家发出的信号
    connect(user_, &UserPlayer::NotifyGrabLordBet, this, &GameControl::OnGrabBet);
}

void GameControl::InitAllCards()
{
    all_cards_.Clear();
    for(int p = Card::CardPoint::CARD_BEGIN + 1; p < Card::CardPoint::CARD_SJ; ++p)
    {
        for(int s = Card::CardSuit::SUIT_BEGIN + 1; s < Card::CardSuit::SUIT_END; ++s)
        {
            Card card((Card::CardPoint)p, (Card::CardSuit)s);
            all_cards_.Add(card);
        }
    }
    all_cards_.Add(Card(Card::CardPoint::CARD_SJ, Card::CardSuit::SUIT_BEGIN));
    all_cards_.Add(Card(Card::CardPoint::CARD_BJ, Card::CardSuit::SUIT_BEGIN));
}

void GameControl::OnGrabBet(Player *player, int bet)
{
    if(bet == 0 || bet_record_.bet >= bet)
    {
        emit GameControlNotifyGrabLordBet(player, 0, false);
    }
    else if(bet > 0 && bet_record_.bet == 0)
    {
        emit GameControlNotifyGrabLordBet(player, bet, true);
    }
    else
    {
        emit GameControlNotifyGrabLordBet(player, bet, false);
    }

    qDebug() << "current player name: " << player->GetName() << ", bet point = " << bet;

    if(bet_record_.bet < bet)
    {
        bet_record_.bet = bet;
        bet_record_.player = player;
    }
    bet_record_.time++;

    if(bet_record_.time == 3)
    {
        return;
    }

    /// 切换玩家，通知下一个玩家继续叫地主
    curr_player_ = player->GetNextPlayer();
    /// 发送信号给主界面, 告知当前状态为抢地主
    emit PlayerStatusChanged(curr_player_, THINKING_FOR_CALL_LORD);
    curr_player_->PrepareCallLord();
}

void GameControl::SetCurrentPlayer(Player *player)
{
    curr_player_ = player;
}

void GameControl::StartLordCard()
{
    emit PlayerStatusChanged(curr_player_, PlayerStatus::THINKING_FOR_CALL_LORD);
}

Player *GameControl::GetCurrentPlayer()
{
    return curr_player_;
}

Player *GameControl::GetLeftRobot()
{
    return robot_left_;
}

Player *GameControl::GetRightRobot()
{
    return robot_right_;
}

Player *GameControl::GetUserPlayer()
{
    return user_;
}

Card GameControl::TakeOneCard()
{
    return all_cards_.TakeRandomCard();
}

Cards GameControl::GetSurplusCards()
{
    return all_cards_;
}
