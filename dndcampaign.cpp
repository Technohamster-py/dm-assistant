//
// Created by akhomchenko on 04.04.24.
//

#include "dndcampaign.h"

dndCampaign::dndCampaign(QString campaignTitle) {
    m_campaignTitle = campaignTitle;

    for (int i = 0; i < 10; ++i) {
        QSharedPointer<QPlayer> player(new QPlayer(nullptr, i % 10));
        m_players.append(player);
    }
}

dndCampaign::dndCampaign(QFile *xmlConfig) {
}

dndCampaign::~dndCampaign() {

}

void dndCampaign::rename(QString newTitle) {
    m_campaignTitle = newTitle;
    emit titleChanged();
}

void dndCampaign::doLongRest() {
    for (int i = 0; i < m_characters.count(); ++i) {
        m_characters.at(i).data()->setFullHp();
    }
}
