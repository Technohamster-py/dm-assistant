//
// Created by arseniy on 03.04.2024.
//

#include "encounter.h"

Encounter::Encounter() {
    m_encounterModel = new QStandardItemModel();
    m_encounterModel->setHorizontalHeaderLabels(QStringList() << "" << "" << "AC" << "HP");

}

Encounter::~Encounter() {

}

void Encounter::addCharacter(Character character) {
    EncounterEntity characterEntity(&character, false);

    QList<QStandardItem *> items;
    items.append(new QStandardItem(characterEntity.getInitiativeValue()));
    items.append(new QStandardItem(characterEntity.getTitle()));
    items.append(new QStandardItem(characterEntity.getAC()));

    QString hpToMaxHp = QString::number(characterEntity.getHP()) + "/" + QString::number(characterEntity.getMaxHp());

    items.append(new QStandardItem(hpToMaxHp));
    m_encounterModel->appendRow(items);

    m_entities.push_back(characterEntity);
}

void Encounter::addMonster(Monster monster) {
    EncounterEntity monsterEntity(&monster, false);

    QList<QStandardItem *> items;
    items.append(new QStandardItem(monsterEntity.getInitiativeValue()));
    items.append(new QStandardItem(monsterEntity.getTitle()));
    items.append(new QStandardItem(monsterEntity.getAC()));

    QString hpToMaxHp = QString::number(monsterEntity.getHP()) + "/" + QString::number(monsterEntity.getMaxHp());

    items.append(new QStandardItem(hpToMaxHp));
    m_encounterModel->appendRow(items);

    m_entities.push_back(monsterEntity);
}


EncounterEntity::EncounterEntity(Character *entity, int initiativeRoll, bool autoAddBonus) {
    m_type = character;
    m_title = entity->getTitle();
    m_character = entity;
    m_characterSheetId = entity->getCharacterSheetId();
    m_ac = entity->getAc();
    m_hp = entity->getHp();
    m_maxHp = entity->getMaxHp();
    m_initiativeBonus = entity->getInitiativeBonus();

    setInitiativeValue(initiativeRoll, autoAddBonus);
}

EncounterEntity::EncounterEntity(Monster *entity, int initiativeRoll, bool autoAddBonus) {
    m_type = monster;
    m_characterSheetId = entity->getCharacterSheetId();
    m_ac = entity->getAc();
    m_hp = entity->getHp();
    m_maxHp = entity->getMaxHp();
    m_initiativeBonus = entity->getInitiativeBonus();

    setInitiativeValue(initiativeRoll, autoAddBonus);
}

EncounterEntity::~EncounterEntity() {

}

void EncounterEntity::setInitiativeValue(int initiativeRoll, bool autoAddBonus) {
    if(autoAddBonus)
        m_initiativeValue = initiativeRoll + m_initiativeBonus;
    else
        m_initiativeValue = initiativeRoll;
}

void EncounterEntity::setHp(int value) {
    if(value <= m_maxHp){
        if(m_type == character)
            m_character->setHp(value);
        m_hp = value;
    }
}

void EncounterEntity::setMaxHp(int value) {
    if(m_type == character)
        m_character->setMaxHp(value);
    m_maxHp = value;
}

