#include "game_pannel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game_pannel w;
    w.show();
    return a.exec();
}
