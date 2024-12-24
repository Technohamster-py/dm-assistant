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
    saveConfigFile();
    delete ui;
}

void MainWindow::configurePlayers() {

    QPlayer* player;
    for (int i = 0; i < 9; ++i) {
        player = new QPlayer(nullptr, i);
        playerList.append(player);
    }

     ui->label1->setText(playerList[0]->getPlaylistName());
     ui->label2->setText(playerList[1]->getPlaylistName());
     ui->label3->setText(playerList[2]->getPlaylistName());
     ui->label4->setText(playerList[3]->getPlaylistName());
     ui->label5->setText(playerList[4]->getPlaylistName());
     ui->label6->setText(playerList[5]->getPlaylistName());
     ui->label7->setText(playerList[6]->getPlaylistName());
     ui->label8->setText(playerList[7]->getPlaylistName());
     ui->label9->setText(playerList[8]->getPlaylistName());

     connect(ui->play1, SIGNAL(clicked(bool)), playerList[0], SLOT(play()));
     connect(ui->play2, SIGNAL(clicked(bool)), playerList[1], SLOT(play()));
     connect(ui->play3, SIGNAL(clicked(bool)), playerList[2], SLOT(play()));
     connect(ui->play4, SIGNAL(clicked(bool)), playerList[3], SLOT(play()));
     connect(ui->play5, SIGNAL(clicked(bool)), playerList[4], SLOT(play()));
     connect(ui->play6, SIGNAL(clicked(bool)), playerList[5], SLOT(play()));
     connect(ui->play7, SIGNAL(clicked(bool)), playerList[6], SLOT(play()));
     connect(ui->play8, SIGNAL(clicked(bool)), playerList[7], SLOT(play()));
     connect(ui->play9, SIGNAL(clicked(bool)), playerList[8], SLOT(play()));

     connect(playerList[0], SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(playerList[1], SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(playerList[2], SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(playerList[3], SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(playerList[4], SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(playerList[5], SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(playerList[6], SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(playerList[7], SIGNAL(playerStarted()), this, SLOT(stopAll()));
     connect(playerList[8], SIGNAL(playerStarted()), this, SLOT(stopAll()));

     connect(ui->edit1, SIGNAL(clicked(bool)), playerList[0], SLOT(edit()));
     connect(ui->edit2, SIGNAL(clicked(bool)), playerList[1], SLOT(edit()));
     connect(ui->edit3, SIGNAL(clicked(bool)), playerList[2], SLOT(edit()));
     connect(ui->edit4, SIGNAL(clicked(bool)), playerList[3], SLOT(edit()));
     connect(ui->edit5, SIGNAL(clicked(bool)), playerList[4], SLOT(edit()));
     connect(ui->edit6, SIGNAL(clicked(bool)), playerList[5], SLOT(edit()));
     connect(ui->edit7, SIGNAL(clicked(bool)), playerList[6], SLOT(edit()));
     connect(ui->edit9, SIGNAL(clicked(bool)), playerList[7], SLOT(edit()));
     connect(ui->edit1, SIGNAL(clicked(bool)), playerList[8], SLOT(edit()));

     playerList[0]->setPlayShortcut("Ctrl+1");
     playerList[1]->setPlayShortcut("Ctrl+2");
     playerList[2]->setPlayShortcut("Ctrl+3");
     playerList[3]->setPlayShortcut("Ctrl+4");
     playerList[4]->setPlayShortcut("Ctrl+5");
     playerList[5]->setPlayShortcut("Ctrl+6");
     playerList[6]->setPlayShortcut("Ctrl+7");
     playerList[7]->setPlayShortcut("Ctrl+8");
     playerList[8]->setPlayShortcut("Ctrl+9");
}

void MainWindow::stopAll() {
    for (int i = 0; i < 9; ++i) {
        playerList[i]->stop();
    }
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
            playerList[i]->loadFromXml(&playerFile);
        }
    }
}

void MainWindow::saveConfigFile() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save to"),
                                                    QDir::homePath(),
                                                    tr("xml file (*.xml)"));
    if(fileName.isEmpty())
        return;
    else{
        QFile configFile(fileName);
        if (!configFile.open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this, tr("Open file error"), configFile.errorString());
            return;
        }
        QFileInfo fileInfo(configFile.fileName());

        QTextStream xmlContent(&configFile);
        QDomDocument configDocument;

        QDomElement root = configDocument.createElement("music-player");
        configDocument.appendChild(root);

        QString baseDir = fileInfo.dir().canonicalPath() + "/";

        for (int i = 0; i < 9; ++i) {
            QString playerFileName = QString("playlist%1.xml").arg(QString::number(i));
            playerList[i]->saveToXml(baseDir + playerFileName);
            QDomElement playlist_node = configDocument.createElement("playlist");
            playlist_node.setAttribute("id", i);
            playlist_node.setNodeValue(playerFileName);
            root.appendChild(playlist_node);
        }
        xmlContent << configDocument.toString();
    }
}
