//
// Created by arsen on 01.04.2024.
//

#include "character.h"

Character::Character(QString characterName) : Creature(characterName) {

}

Character::Character(QFile *xmlConfig) : Creature(xmlConfig) {

}
