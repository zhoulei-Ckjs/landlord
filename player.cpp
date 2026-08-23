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

void Player::SetPrevPlayer(Player *prev)
{
    prev_ = prev;
}

void Player::SetRole(Role role)
{
    role_ = role;
}

void Player::SetSex(Sex sex)
{
    sex_ = sex;
}

Player::Direction Player::GetDirection()
{
    return direction_;
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

Player *Player::GetPrevPlayer()
{
    return prev_;
}

Player::Role Player::GetRole()
{
    return role_;
}

Player::Sex Player::GetSex()
{
    return sex_;
}

void Player::GrabLordBet(int point)
{
    emit NotifyGrabLordBet(this, point);
}

void Player::PrepareCallLord()
{

}

void Player::SetDirection(Direction d)
{
    direction_ = d;
}

void Player::StoreDispatchCard(const Card &card)
{
    cards_.Add(card);
}

void Player::ThinkCallLord()
{

}

Cards Player::GetCards()
{
    return cards_;
}
