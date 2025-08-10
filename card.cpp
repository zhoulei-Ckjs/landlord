#include "card.h"

Card::Card() {}

Card::Card(CardPoint point, CardSuit suit)
{
    setPoint(point);
    setSuit(suit);
}

Card::CardPoint Card::point() const
{
    return point_;
}

void Card::setPoint(CardPoint newPoint)
{
    point_ = newPoint;
}

Card::CardSuit Card::suit() const
{
    return suit_;
}

void Card::setSuit(CardSuit newSuit)
{
    suit_ = newSuit;
}

size_t qHash(const Card& card)
{
    return card.point() * 100 + card.suit();
}

bool operator==(const Card &left, const Card &right)
{
    return (left.point() == right.point() && left.suit() == right.suit());
}
