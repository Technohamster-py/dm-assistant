//
// Created by arsen on 06.03.2024.
//

#include "qplayer.h"
#include "ui_QPlayer.h"
#include "qplaylistedit.h"
#include "QMessageBox"
#include <QFileInfo>
#include <QDir>


QPlayer::QPlayer(QWidget *parent, QString title, int numId) :
        QWidget(parent), ui(new Ui::QPlayer) {
    ui->setupUi(this);

    id = numId;
    playlistName = title;

    ui->titleLabel->setText(playlistName);
    ui->numberLabel->setText(QString::number(id));

    playKey = new QShortcut(this);

    m_player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(playlist);

    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    connect(ui->stopButton, &QPushButton::clicked, m_player, &QMediaPlayer::stop);
    connect(ui->pauseButton, &QPushButton::clicked, m_player, &QMediaPlayer::pause);
    connect(ui->nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui->prevButton, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);
    connect(playKey, SIGNAL(activated()), this, SLOT(playShortcutTriggered()));
}

QPlayer::QPlayer(QWidget *parent, QFile *xmlFile) :
        QWidget(parent), ui(new Ui::QPlayer) {
    ui->setupUi(this);

    m_player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(playlist);

    playKey = new QShortcut(this);

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
    ui->titleLabel->setText(playlistName);
    ui->numberLabel->setText(QString::number(id));

    QString xmlConfigPath = QCoreApplication::applicationDirPath() + "/configs/" + id + "_playlist.xml";

    m_player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    m_player->setPlaylist(playlist);

    playKey = new QShortcut(this);

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

/**
 * Открыть окно изменения плейлиста
 */
void QPlayer::on_editButton_clicked() {
    QPlaylistEdit(nullptr, this).exec();
    ui->titleLabel->setText(playlistName);
}

/**
 * Задать название плейлиста
 * @param name название
 */
void QPlayer::setPlaylistName(QString name) {
    if(name != playlistName){
        playlistName = name;
        emit playlistNameChanged();
    }
}

/**
 * Загрузить существующий плейлист из .xml файла
 * @param xmlFile
 */
void QPlayer::loadFromXml(QFile *xmlFile) {
    if(!xmlFile->open(QIODevice::ReadWrite)){
        QString message = tr("Can not open XML config: ") + xmlFile->errorString();
        QMessageBox::critical(this,
                              tr("File error"),
                              message);
        return;
    }

    xmlConfig.setContent(xmlFile);
    QFileInfo fileInfo(xmlFile->fileName());

    QDomElement playlistNode = xmlConfig.documentElement();
    playlistName = playlistNode.attribute("name");
    id = playlistNode.attribute("id").toInt();
    QDomNodeList tracks = playlistNode.childNodes();

    for (int i = 0; i < tracks.count(); ++i) {
        QDomElement trackNode = tracks.at(i).toElement();
        QString absolutePath = fileInfo.dir().canonicalPath() + "/" + trackNode.firstChild().toText().data();
        playlist->addMedia(QUrl(absolutePath));
    }
    xmlFile->close();
}

/**
 * Записать плейлист в .xml файл
 * @param pathToXml
 */
void QPlayer::saveToXml(QString pathToXml) {
    QString configFileNamePath;
    if(pathToXml == QCoreApplication::applicationDirPath()){
        configFileNamePath = pathToXml + "/configs/" + QString::number(id) + "_playlist.xml";
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

    xmlConfig.clear();

    QDomElement root = xmlConfig.createElement("playlist");
    root.setAttribute("name", playlistName);
    root.setAttribute("id", id);
    xmlConfig.appendChild(root);

    QString audioFilePath;
    QDomElement trackNode;

    for (int i = 0; i < playlist->mediaCount(); ++i) {
        audioFilePath = playlist->media(i).canonicalUrl().toString();
        trackNode = xmlConfig.createElement("file");
        trackNode.setNodeValue(audioFilePath);

        root.appendChild(trackNode);
    }

    xmlContent << xmlConfig.toString();
}

void QPlayer::playShortcutTriggered() {
    play();
}

void QPlayer::stop() {
    emit  playerStopped();
    isActive = false;
    m_player->stop();
}

void QPlayer::play() {
    emit playerStarted();
    qDebug() << "player " << id << "started";
    isActive = true;
    m_player->play();
}

void QPlayer::on_playButton_clicked() {
    play();
}

/**
 * Задать сочетание клавиш для старта прогирывания
 * @param key сочетание клавиш английской раскладки
 */
void QPlayer::setPlayShortcut(QString key) {
    playKey->setKey(key);
}
