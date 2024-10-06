//
// Created by arseniy on 12.03.2024.
//

#include "qplaylistedit.h"
#include "ui_qplaylistedit.h"

#include <QFileDialog>
#include <QDir>
#include <QApplication>


QPlaylistEdit::QPlaylistEdit(QWidget *parent, QPlayer *player) :
        QDialog(parent), ui(new Ui::QPlaylistEdit) {
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("Edit playlist"));

    ui->titleEdit->setText(player->getPlaylistName());

    m_player = player;
    m_playlistModel = new QStandardItemModel(this);
    m_playlistModel->setHorizontalHeaderLabels(QStringList() << tr("Track title") << tr("File path"));

    ui->playlistView->setModel(m_playlistModel);
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

    displayPlaylist();
}

QPlaylistEdit::~QPlaylistEdit() {
    delete ui;
}

void QPlaylistEdit::on_addButton_clicked() {
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Add tracks"),
                                                      QString(),
                                                      tr("Audio files (*.mp3)"));

    foreach (QString filePath, files){
        QList<QStandardItem *> items;

        QString localDirPath = QCoreApplication::applicationDirPath() + "/playlists/" + QString::number(m_player->getId()) + "_playlist";

        QStringList fileDirs = filePath.split("/");
        QString fileName = fileDirs.at(fileDirs.size()-1);
        QString copiedFilePath = localDirPath + "/" + fileName;

        if(!QDir(localDirPath).exists()){
            QDir().mkpath(localDirPath);
        }

        //qDebug() << copiedFilePath;

        QFile::copy(filePath, copiedFilePath);

        items.append((new QStandardItem(QDir(copiedFilePath).dirName())));
        items.append(new QStandardItem(copiedFilePath));
        m_playlistModel->appendRow(items);
        m_player->playlist->addMedia(QUrl(copiedFilePath));
    }
}
void QPlaylistEdit::on_removeButton_clicked() {
    int index = ui->playlistView->selectionModel()->selection().indexes()[0].row();
    m_playlistModel->removeRow(index);
    m_player->playlist->removeMedia(index);
}

void QPlaylistEdit::on_buttonBox_accepted() {
    m_player->setPlaylistName(ui->titleEdit->text());
    accept();
}

void QPlaylistEdit::on_buttonBox_rejected() {
    reject();
}

void QPlaylistEdit::displayPlaylist() {
    for (int i = 0; i < m_player->playlist->mediaCount(); ++i) {
        QList<QStandardItem *> items;
        QString filePath =  m_player->playlist->media(i).canonicalUrl().toString();
        items.append((new QStandardItem(QDir(filePath).dirName())));
        items.append(new QStandardItem(filePath));
        m_playlistModel->appendRow(items);
    }
}
