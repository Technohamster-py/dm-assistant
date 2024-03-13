//
// Created by arseniy on 12.03.2024.
//

#ifndef DM_ASSIST_QPLAYLISTEDIT_H
#define DM_ASSIST_QPLAYLISTEDIT_H

#include <QDialog>
#include <QStandardItemModel>
#include "qplayer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class QPlaylistEdit; }
QT_END_NAMESPACE

class QPlaylistEdit : public QDialog {
Q_OBJECT

public:
    explicit QPlaylistEdit(QWidget *parent = nullptr, QPlayer *player = nullptr);

    ~QPlaylistEdit() override;

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::QPlaylistEdit *ui;
    QPlayer *m_player;
    QStandardItemModel *m_playlistModel;

    int m_selectedIndex;
};


#endif //DM_ASSIST_QPLAYLISTEDIT_H
