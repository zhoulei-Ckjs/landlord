/**
 * @brief 分数面板窗口
 *
 * 进行分数统计
 */

#ifndef SCORE_PANEL_H
#define SCORE_PANEL_H

#include <QWidget>

namespace Ui {
class ScorePanel;
}

class ScorePanel : public QWidget
{
    Q_OBJECT

public:
    explicit ScorePanel(QWidget *parent = nullptr);
    ~ScorePanel();

    /**
     * @brief 设置玩家得分
     * @param left 左侧玩家得分
     * @param right 右侧玩家得分
     * @param user 玩家得分
     */
    void SetScores(int left, int right, int user);

private:
    Ui::ScorePanel *ui;
};

#endif // SCORE_PANEL_H
