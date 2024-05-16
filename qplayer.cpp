//
// Created by arsen on 06.03.2024.
//

#include "qplayer.h"
#include "ui_qplayer.h"
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

QPlayer::QPlayer(QWidget *parent, int numId) : QWidget(parent), ui(new Ui::QPlayer) {
    ui->setupUi(this);
    id = numId;

    QString xmlConfigPath = QCoreApplication::applicationDirPath() + "/configs/" + id + "_playlist.xml";

    m_player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(playlist);

    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    connect(ui->playButton, &QPushButton::clicked, m_player, &QMediaPlayer::play);
    connect(ui->stopButton, &QPushButton::clicked, m_player, &QMediaPlayer::stop);
    connect(ui->pauseButton, &QPushButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui->prevButton, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);

    QFile *xmlFile = new QFile(xmlConfigPath);
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
    m_xmlConfig.setContent(xmlFile);
    xmlFile->close();

    QDomElement playlistNode = m_xmlConfig.documentElement();
    playlistName = playlistNode.attribute("name");
    id = playlistNode.attribute("id").toInt();
    QDomNodeList tracks = playlistNode.childNodes();

    for (int i = 0; i < tracks.count(); ++i) {
        QDomElement trackNode = tracks.at(i).toElement();
        playlist->addMedia(QUrl(trackNode.firstChild().toText().data()));
    }
}

void QPlayer::saveToXml(QString pathToXml) {
    QString configFileNamePath;
    if(pathToXml == QCoreApplication::applicationDirPath()){
        configFileNamePath = pathToXml + "/configs/" + id + "_playlist.xml";
    } else
    {
        configFileNamePath = pathToXml;
    }
    QFile config(configFileNamePath);

    if (!config.open(QFile::WriteOnly))
    {
        QMessageBox::critical(this,
                              tr("XML file error"),
                              tr("Can not open XML config file") + config.errorString());
        return;
    }

    QTextStream xmlContent(&config);

    m_xmlConfig.clear();

    QDomElement root = m_xmlConfig.createElement("playlist");
    root.setAttribute("name", playlistName);
    root.setAttribute("id", id);
    m_xmlConfig.appendChild(root);

    QString audioFilePath;
    QDomElement trackNode;

    for (int i = 0; i < playlist->mediaCount(); ++i) {
        audioFilePath = playlist->media(i).canonicalUrl().toString();
        trackNode = m_xmlConfig.createElement("file");
        trackNode.setNodeValue(audioFilePath);

        root.appendChild(trackNode);
    }

    xmlContent << m_xmlConfig.toString();
}
