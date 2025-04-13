/**
 * @brief 按钮组窗口
 */

#ifndef BUTTON_GROUP_H
#define BUTTON_GROUP_H

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    /**
     * @brief 初始化按钮
     */
    void InitButtons();

    /**
     * @brief 处理配置页的切换
     */
    void SelectPanel();

private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTON_GROUP_H
