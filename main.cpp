#include <QApplication>
#include <QPushButton>
#include <qfile.h>
#include "qplayerwidget.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();
}
