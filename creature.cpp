//
// Created by arsen on 01.04.2024.
//

#include "creature.h"
#include <utility>

Creature::Creature(QString creatureName) {
    title = std::move(creatureName);
}

Creature::Creature(QFile *xmlConfig) {

}

int Creature::loadFromFile(QFile *xmlConfig) {
    return 0;
}

int Creature::saveToFile(QFile *xmlConfig) {
    return 0;
}
