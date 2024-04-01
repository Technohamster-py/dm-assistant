//
// Created by arsen on 01.04.2024.
//

#include "monster.h"

Monster::Monster(QString monsterTitile) : Creature(monsterTitile) {

}

Monster::Monster(QFile *xmlConfig) : Creature(xmlConfig) {

}

Monster::~Monster() {

}
