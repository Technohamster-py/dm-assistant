//
// Created by arsen on 06.03.2024.
//

#ifndef DM_ASSIST_QPLAYER_H
#define DM_ASSIST_QPLAYER_H

#include <QWidget>
//#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>


QT_BEGIN_NAMESPACE
namespace Ui { class QPlayer; }
QT_END_NAMESPACE

class QPlayer : public QWidget {
Q_OBJECT

public:
    QPlayer(QWidget *parent, QString title, int numId);

    ~QPlayer() override;

    int id;

private slots:
    void on_editButton_clicked();

private:
    Ui::QPlayer *ui;

    //QStandardItemModel *m_playlistModel; ///< Модель данных плейлиста для отображения
    QMediaPlayer *m_player; ///< Проигрыватель
    QMediaPlaylist *m_playlist; ///< Плейлист проигрывателя
};


#endif //DM_ASSIST_QPLAYER_H
