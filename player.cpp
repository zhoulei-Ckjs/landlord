#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{}

Player::Player(QString name, QObject *parent)
{
    SetName(name);
}

void Player::SetNextPlayer(Player *next)
{
    next_ = next;
}

void Player::SetName(QString name)
{
    name_ = name;
}

QString Player::GetName()
{
    return name_;
}

Player *Player::GetNextPlayer()
{
    return next_;
}

void Player::GrabLordBet(int point)
{
    emit NotifyGrabLordBet(this, point);
}

void Player::PrepareCallLord()
{

}

void Player::StoreDispatchCard(const Card &card)
{
    cards_.Add(card);
}

Cards Player::GetCards()
{
    return cards_;
}
