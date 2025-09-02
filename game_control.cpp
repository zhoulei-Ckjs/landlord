#include "game_control.h"

GameControl::GameControl(QObject *parent)
    : QObject{parent}
{}

void GameControl::PlayerInit()
{
    /// 对象初始化
    robot_left_ = new Robot(this);
    robot_right_ = new Robot(this);
    user_ = new UserPlayer(this);

    /// 出牌顺序
    user_->SetNextPlayer(robot_left_);
    robot_right_->SetNextPlayer(user_);
    robot_left_->SetNextPlayer(robot_right_);

    /// 指定当前玩家
    curr_player_ = user_;
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

void GameControl::SetCurrentPlayer(Player *player)
{
    curr_player_ = player;
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
