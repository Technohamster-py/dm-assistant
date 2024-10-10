#include <QApplication>
#include <QPushButton>
#include <qfile.h>
#include "qplayer.h"
#include <QDomDocument>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QFile file("D:\\documents\\dm_assist_campains\\cam1\\playlist.xml");
    QPlayer player(nullptr, &file);
    //player.setPlayShortcut("Ctrl+0");
    player.show();
    return QApplication::exec();
}
