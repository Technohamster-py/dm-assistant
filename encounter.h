//
// Created by arseniy on 03.04.2024.
//

#ifndef DM_ASSIST_ENCOUNTER_H
#define DM_ASSIST_ENCOUNTER_H

#include "character.h"
#include "monster.h"

class Encounter {
public:
    Encounter();
    ~Encounter();

    void addCharacter(Character character);
    void addMonster(Monster monster);

private:
    QVector<Character> m_characters;
    QVector<Monster> m_monsters;
};


#endif //DM_ASSIST_ENCOUNTER_H
