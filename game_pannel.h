#ifndef GAME_PANNEL_H
#define GAME_PANNEL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class game_pannel;
}
QT_END_NAMESPACE

class game_pannel : public QMainWindow
{
    Q_OBJECT

public:
    game_pannel(QWidget *parent = nullptr);
    ~game_pannel();

private:
    Ui::game_pannel *ui;
};
#endif // GAME_PANNEL_H
