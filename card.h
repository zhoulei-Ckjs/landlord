/**
 * @file 卡牌类
 */

#ifndef CARD_H
#define CARD_H

#include <QVector>

class Card
{
public:
    /// 卡牌花色
    enum CardSuit
    {
        SUIT_BEGIN,
        DIAMOND,
        CLUB,
        HEART,
        SPADE,
        SUIT_END
    };

    /// 卡牌点数
    enum CardPoint
    {
        CARD_BEGIN,
        CARD_3,
        CARD_4,
        CARD_5,
        CARD_6,
        CARD_7,
        CARD_8,
        CARD_9,
        CARD_10,
        CARD_J,
        CARD_Q,
        CARD_K,
        CARD_A,
        CARD_2,
        CARD_SJ,    // small joker
        CARD_BJ,     // big joker
        CARD_END
    };

    Card();
    Card(CardPoint point, CardSuit suit);

    CardPoint point() const;
    void setPoint(CardPoint newPoint);

    CardSuit suit() const;
    void setSuit(CardSuit newSuit);

private:
    CardPoint point_;   ///< 点数
    CardSuit suit_;     ///< 花色
};

/// 对象比较
bool LessSort(const Card& card1, const Card& card2);
bool GreaterSort(const Card& card1, const Card& card2);

bool operator==(const Card& left, const Card& right);
bool operator<(const Card& card1, const Card& card2);

/**
 * @brief 由于qSet<Card>需要对插入的元素进行去重，利用qHash进行比较，所以需要实现全局函数qHash的重载
 */
size_t qHash(const Card& card);

#endif // CARD_H
