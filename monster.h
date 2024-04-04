//
// Created by arsen on 01.04.2024.
//

#ifndef DM_ASSIST_MONSTER_H
#define DM_ASSIST_MONSTER_H

#include "dndcreature.h"

class Monster : public dndCreature {
public:
    explicit Monster(QString monsterTitile);
    explicit Monster(QFile *xmlConfig);

    ~Monster();

private:
    QMap<QString, bool> m_skillsProficiency;    ///< skill - has proficiency
    QMap<QString, bool> m_savesProficiency;    ///< Save throw - has proficiency

    QMap<QString, QString> m_feelings;    ///< feeling name - description

    QMap<QString, QString> m_abilities;    ///< Ability name - description

    QMap<QString, QString> m_actions;

    QString m_area;
    QString m_description;
};


#endif //DM_ASSIST_MONSTER_H
