//
// Created by arsen on 06.03.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QPlayer.h" resolved

#include "qplayer.h"
#include "ui_QPlayer.h"
#include "qplaylistedit.h"


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

QPlayer::~QPlayer() {
    delete ui;
    delete m_player;
    delete playlist;
}

void QPlayer::on_editButton_clicked() {
    //QPlaylistEdit(nullptr, this);
}
