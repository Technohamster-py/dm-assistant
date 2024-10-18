 //
// Created by arseniy on 11.10.2024.
//
#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QFile"
#include "QFileInfo"
#include "QDomDocument"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    configurePlayers();
}

MainWindow::~MainWindow() {
    delete ui;
}

 void MainWindow::configurePlayers() {
     player1 = new QPlayer(ui->player1, 1);
     player2 = new QPlayer(ui->player2, 2);
     player3 = new QPlayer(ui->player3, 3);
     player4 = new QPlayer(ui->player4, 4);
     player5 = new QPlayer(ui->player5, 5);
     player6 = new QPlayer(ui->player6, 6);
     player7 = new QPlayer(ui->player7, 7);
     player8 = new QPlayer(ui->player8, 8);
     player9 = new QPlayer(ui->player9, 9);

     ui->label1.setText(player1->getPlaylistName());
     ui->label2.setText(player2->getPlaylistName());
     ui->label3.setText(player3->getPlaylistName());
     ui->label4.setText(player4->getPlaylistName());
     ui->label5.setText(player5->getPlaylistName());
     ui->label6.setText(player6->getPlaylistName());
     ui->label7.setText(player7->getPlaylistName());
     ui->label8.setText(player8->getPlaylistName());
     ui->label9.setText(player9->getPlaylistName());

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
    player1->stop();
    player2->stop();
    player3->stop();
    player4->stop();
    player5->stop();
    player6->stop();
    player7->stop();
    player8->stop();
    player9->stop();
 }

 void MainWindow::loadConfigFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open player config file"),
                                                    QDir::homePath(),
                                                    tr("Xml file (*.xml)"));
    if(fileName.isEmpty())
        return;
    else
    {
        QFile configFile(fileName);
        if (!configFile.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Open File error"), configFile.errorString());
            return;
        }
        QDomDocument configDocument;
        configDocument.setContent(&configFile);
        QFileInfo fileInfo(configFile.fileName());

        QDomElement mainNode = configDocument.documentElement();
        QDomNodeList players = mainNode.childNodes();

        for (int i=0; i<players.count(); i++){
            QDomElement playerNode = players.at(i).toElement();
            QString absolutePath = fileInfo.dir().canonicalPath() + "/" + playerNode.firstChild().toText().data();
            int playerId = playerNode.attribute("id").toInt();
            QFile playerFile(absolutePath);
            switch (playerId) {
                case 1:
                    player1->loadFromXml(&playerFile);
                    break;
                case 2:
                    player2->loadFromXml(&playerFile);
                    break;
                case 3:
                    player3->loadFromXml(&playerFile);
                    break;
                case 4:
                    player4->loadFromXml(&playerFile);
                    break;
                case 5:
                    player5->loadFromXml(&playerFile);
                    break;
                case 6:
                    player6->loadFromXml(&playerFile);
                    break;
                case 7:
                    player7->loadFromXml(&playerFile);
                    break;
                case 8:
                    player8->loadFromXml(&playerFile);
                    break;
                case 9:
                    player9->loadFromXml(&playerFile);
                    break;
                default:
                    break;
            }
        }
    }
 }
