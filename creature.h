//
// Created by arsen on 01.04.2024.
//

#ifndef DM_ASSIST_CREATURE_H
#define DM_ASSIST_CREATURE_H

#include <QString>
#include <QFile>
#include <QMap>

class Creature {
public:
    explicit Creature(QString creatureName);
    explicit Creature(QFile *xmlConfig)

    ~Creature();

    int loadFromFile(QFile *xmlConfig = nullptr);
    int saveToFile(QFile *xmlConfig = nullptr);

protected:
    QString title;
    QString notes;

    QFile image;

    int strength = 10;
    int constitution = 10;
    int dexterity = 10;
    int wisdom = 10;
    int intelligence = 10;
    int charisma = 10;

    int initiative = 10;

    int ac = 10;
    int maxHP = 0;
    QString hpFormula = "";

    QMap<QString, int> speedValues;
};


#endif //DM_ASSIST_CREATURE_H
