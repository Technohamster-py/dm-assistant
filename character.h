//
// Created by arsen on 01.04.2024.
//

#ifndef DM_ASSIST_CHARACTER_H
#define DM_ASSIST_CHARACTER_H

#include "creature.h"

class Character : Creature{
public:
    explicit Character(QString characterName);
    explicit Character(QFile *xmlConfig);

    ~Character();

    /// Races from PHB
    enum Races{
        Gnome = 0,
        Dwarf = 1,
        Dragonborn = 2,
        Halforc = 3,
        Halfling = 4,
        Halfelf = 5,
        Tiefling = 6,
        Human = 7,
        Elf = 8
    };

private:
    int id; ///< Unique id of charlist

    int race;
    int age;
    QString gender;

    QMap<QString, int> classLevel;        ///< Class - level
    QMap<QString, QString> subclasses;    ///< Class - subclass

    QMap<QString, bool> skillsProficiency;    ///< skill - has proficiency
    QMap<QString, bool> savesProficiency;    ///< Save throw - has proficiency

    QMap<QString, QString> feelings;    ///< feeling name - description

    QString languages; ///< list of languages

    //inventory
    //spellbook

    QMap<QString, int> friends; ///< Friend name - friend character id
    QMap<QString, int> enemies; ///< Enemy name - enemy character id

    QMap<QString, QString> abilities;    ///< Ability name - description
};


#endif //DM_ASSIST_CHARACTER_H
