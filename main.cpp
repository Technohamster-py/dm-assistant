#include <QApplication>
#include <QPushButton>

#include "qplayer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPlayer player(nullptr, "Test Playlist", 0);
    player.setPlayShortcut("Ctrl+0");
    player.show();
    return QApplication::exec();
}
