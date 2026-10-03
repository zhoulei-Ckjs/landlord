#ifndef ANIMATION_WINDOW_H
#define ANIMATION_WINDOW_H

#include <QWidget>

class AnimationWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationWindow(QWidget *parent = nullptr);

    void ShowBetScore(int bet);

protected:
    void paintEvent(QPaintEvent* ev);

private :
    QPixmap image_;

signals:
};

#endif // ANIMATION_WINDOW_H
