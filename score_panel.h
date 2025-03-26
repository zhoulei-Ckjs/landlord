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

private:
    Ui::ScorePanel *ui;
};

#endif // SCORE_PANEL_H
