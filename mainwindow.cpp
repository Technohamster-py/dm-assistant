//
// Created by akhomchenko on 25.03.24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    configurePlayers();

    initiativeWidget = new QInitiativeTrackerWidget(ui->rightAsideWidget);
    ui->rightAsideLayout->addWidget(initiativeWidget);
    connect(initiativeWidget, SIGNAL(share(Encounter *)), this, SLOT(slotShareTracker(Encounter *)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slotShareTracker(Encounter *encounter) {
    qDebug() << "slotShareTracker";
    //playerInitiativeView = new qPlayerInitiativeView();
}

void MainWindow::configurePlayers() {
    player1 = new QPlayer(ui->musicWidget, 1);
    player2 = new QPlayer(ui->musicWidget, 2);
    player3 = new QPlayer(ui->musicWidget, 3);
    player4 = new QPlayer(ui->musicWidget, 4);
    player5 = new QPlayer(ui->musicWidget, 5);
    player6 = new QPlayer(ui->musicWidget, 6);
    player7 = new QPlayer(ui->musicWidget, 7);
    player8 = new QPlayer(ui->musicWidget, 8);
    player9 = new QPlayer(ui->musicWidget, 9);
    player0 = new QPlayer(ui->musicWidget, 0);

    player1->setPlayShortcut("a");
    player2->setPlayShortcut("Ctrl+2");
    player3->setPlayShortcut("Ctrl+3");
    player4->setPlayShortcut("Ctrl+4");
    player5->setPlayShortcut("Ctrl+5");
    player6->setPlayShortcut("Ctrl+6");
    player7->setPlayShortcut("Ctrl+7");
    player8->setPlayShortcut("Ctrl+8");
    player9->setPlayShortcut("Ctrl+9");
    player0->setPlayShortcut("Ctrl+0");

    connect(player1, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player2, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player3, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player4, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player5, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player6, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player7, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player8, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player9, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));
    connect(player0, SIGNAL(playerStarted()), this, SLOT(stopAllMusic()));

    ui->musicLayout->addWidget(player1);
    ui->musicLayout->addWidget(player2);
    ui->musicLayout->addWidget(player3);
    ui->musicLayout->addWidget(player4);
    ui->musicLayout->addWidget(player5);
    ui->musicLayout->addWidget(player6);
    ui->musicLayout->addWidget(player7);
    ui->musicLayout->addWidget(player8);
    ui->musicLayout->addWidget(player9);
    ui->musicLayout->addWidget(player0);
}

void MainWindow::stopAllMusic() {
    player1->stop();
    player2->stop();
    player3->stop();
    player4->stop();
    player5->stop();
    player6->stop();
    player7->stop();
    player8->stop();
    player9->stop();
    player0->stop();
}
