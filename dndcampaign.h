//
// Created by akhomchenko on 04.04.24.
//

#ifndef DM_ASSIST_DNDCAMPAIGN_H
#define DM_ASSIST_DNDCAMPAIGN_H

#include <QString>
#include <QFile>

#include "character.h"
#include "monster.h"
#include "qplayer.h"

class dndCampaign : public QObject{
    Q_OBJECT
public:
    explicit dndCampaign(QString campaignTitle);
    explicit dndCampaign(QFile *xmlConfig);

    ~dndCampaign();

    void rename(QString newTitle);
    void doLongRest();

private:
    QString m_campaignTitle;

    QList<Character> m_characters;
    QList<Monster> m_monsters;
    QList<QPlayer> m_players;
};


#endif //DM_ASSIST_DNDCAMPAIGN_H
