//
// Created by arsen on 01.04.2024.
//

#ifndef DM_ASSIST_MONSTER_H
#define DM_ASSIST_MONSTER_H

#include "creature.h"

class Monster : Creature {
public:
    explicit Monster(QString monsterTitile);
    explicit Monster(QFile *xmlConfig);

    ~Monster();

private:
    QMap<QString, bool> skillsProficiency;    ///< skill - has proficiency
    QMap<QString, bool> savesProficiency;    ///< Save throw - has proficiency

    QMap<QString, QString> feelings;    ///< feeling name - description

    QMap<QString, QString> abilities;    ///< Ability name - description

    QMap<QString, QString> actions;

    QString area;
    QString description;
};


#endif //DM_ASSIST_MONSTER_H
