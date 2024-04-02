//
// Created by arsen on 01.04.2024.
//

#include "monster.h"

Monster::Monster(QString monsterTitile) : dndCreature(monsterTitile) {

}

Monster::Monster(QFile *xmlConfig) : dndCreature(xmlConfig) {

}

Monster::~Monster() {

}
