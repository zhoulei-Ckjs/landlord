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

private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTON_GROUP_H
