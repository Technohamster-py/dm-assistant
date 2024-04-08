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
    QSharedPointer<EncounterEntity> characterEntity(new EncounterEntity(&character, false));

    QList<QStandardItem *> items;
    items.append(new QStandardItem(characterEntity.data()->getInitiativeValue()));
    items.append(new QStandardItem(characterEntity.data()->getTitle()));
    items.append(new QStandardItem(characterEntity.data()->getAC()));

    QString hpToMaxHp = QString::number(characterEntity.data()->getHP()) + "/" + QString::number(characterEntity.data()->getMaxHp());

    items.append(new QStandardItem(hpToMaxHp));
    m_encounterModel->appendRow(items);

    m_entities.append(characterEntity);
}

void Encounter::addMonster(Monster monster) {
    QSharedPointer<EncounterEntity> monsterEntity(new EncounterEntity(&monster, false));

    QList<QStandardItem *> items;
    items.append(new QStandardItem(monsterEntity.data()->getInitiativeValue()));
    items.append(new QStandardItem(monsterEntity.data()->getTitle()));
    items.append(new QStandardItem(monsterEntity.data()->getAC()));

    QString hpToMaxHp = QString::number(monsterEntity.data()->getHP()) + "/" + QString::number(monsterEntity.data()->getMaxHp());

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

