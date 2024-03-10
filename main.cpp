#include <QApplication>
#include <QPushButton>

#include "qplayer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPlayer player;
    player.show();
    return QApplication::exec();
}
