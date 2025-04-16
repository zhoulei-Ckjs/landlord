/**
 * @file 主窗口类
 */

#ifndef GAME_PANEL_H
#define GAME_PANEL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class GamePanel;
}
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();

protected:
    /**
     * @brief 游戏主窗口绘图事件
     */
    void paintEvent(QPaintEvent* e);

private:
    Ui::GamePanel *ui;

    QPixmap background_image_;          ///< 游戏主窗口背景图片
};
#endif // GAME_PANEL_H
