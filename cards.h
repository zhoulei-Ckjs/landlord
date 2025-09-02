/**
 * @brief 多张卡牌类
 */

#ifndef CARDS_H
#define CARDS_H

#include "card.h"

#include <QSet>

class Cards
{
public:
    Cards();

    /**
     * @brief Add 添加扑克牌
     * @param card 扑克牌
     */
    void Add(const Card& card);

    /**
     * @brief CardsCount 获取扑克牌数量
     * @return 扑克牌数量
     */
    int CardsCount();

    /**
     * @brief Clear 清空扑克牌
     */
    void Clear();

    /**
     * @brief TakeRandomCard 随机取出一张扑克牌
     * @return 扑克牌
     */
    Card TakeRandomCard();

private:
    QSet<Card> cards_;          ///< 存储的扑克牌
};

#endif // CARDS_H
