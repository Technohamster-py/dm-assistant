//
// Created by arsen on 06.03.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QPlayer.h" resolved

#include "qplayer.h"
#include "ui_QPlayer.h"
#include "qplaylistedit.h"
#include "QMessageBox"


QPlayer::QPlayer(QWidget *parent, QString title, int numId) :
        QWidget(parent), ui(new Ui::QPlayer) {
    ui->setupUi(this);

    id = numId;
    playlistName = title;

    ui->titleLabel->setText(playlistName);
    ui->numberLabel->setText(QString::number(id));

    m_player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(playlist);

    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    connect(ui->playButton, &QPushButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->stopButton, &QPushButton::clicked, m_player, &QMediaPlayer::stop);
    connect(ui->pauseButton, &QPushButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui->prevButton, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);
}

QPlayer::QPlayer(QWidget *parent, QFile *xmlFile) :
        QWidget(parent), ui(new Ui::QPlayer) {
    ui->setupUi(this);

    m_player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(playlist);

    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    connect(ui->playButton, &QPushButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->stopButton, &QPushButton::clicked, m_player, &QMediaPlayer::stop);
    connect(ui->pauseButton, &QPushButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui->prevButton, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);

    loadFromXml(xmlFile);

    ui->titleLabel->setText(playlistName);
    ui->numberLabel->setText(QString::number(id));
}

QPlayer::~QPlayer() {
    delete ui;
    delete m_player;
    delete playlist;
}

void QPlayer::on_editButton_clicked() {
    QPlaylistEdit(nullptr, this).exec();
    ui->titleLabel->setText(playlistName);
}

void QPlayer::setPlaylistName(QString name) {
    if(name != playlistName){
        playlistName = name;
        emit playlistNameChanged();
    }
}

void QPlayer::loadFromXml(QFile *xmlFile) {
    if(!xmlFile->open(QIODevice::ReadWrite)){
        QString message = tr("Can not open XML config: ") + xmlFile->errorString();
        QMessageBox::critical(this,
                              tr("File error"),
                              message);
        return;
    }
    xmlConfig.setContent(xmlFile);
    xmlFile->close();

    QDomElement playlistNode = xmlConfig.documentElement();
    playlistName = playlistNode.attribute("name");
    id = playlistNode.attribute("id").toInt();
    QDomNodeList tracks = playlistNode.childNodes();

    for (int i = 0; i < tracks.count(); ++i) {
        QDomElement trackNode = tracks.at(i).toElement();
        playlist->addMedia(QUrl(trackNode.firstChild().toText().data()));
    }
}
