 //
// Created by arseniy on 11.10.2024.
//
#include "mainwindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    configurePlayers();

}

MainWindow::~MainWindow() {
    delete ui;
}

 void MainWindow::configurePlayers() {
     QPlayer *player1 = new QPlayer(ui->player1, 1);
     QPlayer *player2 = new QPlayer(ui->player2, 2);
     QPlayer *player3 = new QPlayer(ui->player3, 3);
     QPlayer *player4 = new QPlayer(ui->player4, 4);
     QPlayer *player5 = new QPlayer(ui->player5, 5);
     QPlayer *player6 = new QPlayer(ui->player6, 6);
     QPlayer *player7 = new QPlayer(ui->player7, 7);
     QPlayer *player8 = new QPlayer(ui->player8, 8);
     QPlayer *player9 = new QPlayer(ui->player9, 9);

     connect(ui->play1, SIGNAL(clicked(bool)), player1, SLOT(play()));
     connect(ui->play2, SIGNAL(clicked(bool)), player2, SLOT(play()));
     connect(ui->play3, SIGNAL(clicked(bool)), player3, SLOT(play()));
     connect(ui->play4, SIGNAL(clicked(bool)), player4, SLOT(play()));
     connect(ui->play5, SIGNAL(clicked(bool)), player5, SLOT(play()));
     connect(ui->play6, SIGNAL(clicked(bool)), player6, SLOT(play()));
     connect(ui->play7, SIGNAL(clicked(bool)), player7, SLOT(play()));
     connect(ui->play8, SIGNAL(clicked(bool)), player8, SLOT(play()));
     connect(ui->play9, SIGNAL(clicked(bool)), player9, SLOT(play()));

     connect(player1, SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(player2, SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(player3, SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(player4, SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(player5, SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(player6, SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(player7, SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(player8, SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(player9, SIGNAL(playerStarted()), this, SLOT(stopAll()));

     player1->setPlayShortcut("Ctrl+1");
     player2->setPlayShortcut("Ctrl+2");
     player3->setPlayShortcut("Ctrl+3");
     player4->setPlayShortcut("Ctrl+4");
     player5->setPlayShortcut("Ctrl+5");
     player6->setPlayShortcut("Ctrl+6");
     player7->setPlayShortcut("Ctrl+7");
     player8->setPlayShortcut("Ctrl+8");
     player9->setPlayShortcut("Ctrl+9");
 }

 void MainWindow::stopAll() {
    /*player1->stop();
    player2->stop();
    player3->stop();
    player4->stop();
    player5->stop();
    player6->stop();
    player7->stop();
    player8->stop();
    player9->stop();*/
 }
