//
// Created by arsen on 06.03.2024.
//

#ifndef DM_ASSIST_QPLAYER_H
#define DM_ASSIST_QPLAYER_H

#include <QApplication>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFile>
#include <QDomDocument>


QT_BEGIN_NAMESPACE
namespace Ui { class QPlayer; }
QT_END_NAMESPACE

class QPlayer : public QWidget {
Q_OBJECT

public:
    QPlayer(QWidget *parent, QString title, int numId);
    QPlayer(QWidget *parent, QFile *xmlFile);
    QPlayer(QWidget *parent, int numId);

    ~QPlayer() override;

    [[nodiscard]] QString getPlaylistName() const{return playlistName;};
    void setPlaylistName(QString name);

    [[nodiscard]] int getId() const{return id;};

    void saveToXml(QString pathToXml = QCoreApplication::applicationDirPath());

    QMediaPlaylist *playlist; ///< Плейлист проигрывателя

signals:
    void playlistNameChanged();

protected:
    void loadFromXml(QFile *xmlFile);
    QString playlistName;
    int id;

private slots:
    void on_editButton_clicked();

private:
    Ui::QPlayer *ui;
    QDomDocument xmlConfig;

    //QStandardItemModel *m_playlistModel; ///< Модель данных плейлиста для отображения
    QMediaPlayer *m_player; ///< Проигрыватель
};


#endif //DM_ASSIST_QPLAYER_H
