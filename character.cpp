//
// Created by arsen on 01.04.2024.
//

#include "character.h"

Character::Character(QString characterName) : dndCreature(characterName) {

}

Character::Character(QFile *xmlConfig) : dndCreature(xmlConfig) {
    loadFromFile(xmlConfig);
}

void Character::loadFromFile(QFile *xmlConfigFile) {
    int errCode = loadCreatureFromFile(xmlConfigFile);
    if (errCode != ErrorNone){
        return;
    }

    QDomElement characterNode = configDom.documentElement();
    id = characterNode.attribute("id").toInt();

    title = characterNode.firstChildElement("name").toText().data();

    QDomElement raceNode = characterNode.firstChildElement("race");
    raceId = raceNode.attribute("id").toInt();
    race = raceNode.toText().data();

    age = characterNode.firstChildElement("age").toText().data().toInt()

    characteristics["Strength"] = characterNode.firstChildElement("stats").firstChildElement("STR").toText().data().toInt();
    characteristics["Constitution"] = characterNode.firstChildElement("stats").firstChildElement("CON").toText().data().toInt();
    characteristics["Dexterity"] = characterNode.firstChildElement("stats").firstChildElement("DEX").toText().data().toInt();
    characteristics["Wisdom"] = characterNode.firstChildElement("stats").firstChildElement("WIS").toText().data().toInt();
    characteristics["Intelligence"] = characterNode.firstChildElement("stats").firstChildElement("INT").toText().data().toInt();
    characteristics["Charisma"] = characterNode.firstChildElement("stats").firstChildElement("CHA").toText().data().toInt();

    QDomNodeList skillsList = characterNode.elementsByTagName("skill");
    for (int i = 0; i < skillsList.count(); ++i) {
        QDomElement skill = skillsList.at(i).toElement();
        skillsProficiency[skill.attribute("name")] = skill.toText().data().toInt();
    }

    QDomNodeList classesList = characterNode.elementsByTagName("class");
    for (int i = 0; i < classesList.count(); ++i) {
        QDomElement characterClass = classesList.at(i).toElement();
        QString className = characterClass.toText().data();
        int level = characterClass.attribute("level").toInt();
        QString subclass = characterClass.attribute("subclass");
        classLevel[className] = level;
        subclasses[className] = subclass;
    }

    ac = characterNode.firstChildElement("ac").toText().data().toInt();
    hp = characterNode.firstChildElement("hp").attribute("current").toInt();
    maxHP = characterNode.firstChildElement("hp").attribute("max").toInt();

    QDomNodeList feelingsList = characterNode.elementsByTagName("feeling");
    for (int i = 0; i < feelingsList.count(); i++){
        QString feelingName = feelingsList.at(i).toElement().attribute("name");
        QString feelingDescription = feelingsList.at(i).toElement().toText().data();
        feelings[feelingName] = feelingDescription;
    }

    languages = characterNode.firstChildElement("languages").toText().data();

    proficiencyBonus = characterNode.firstChildElement("proficiency-bonus").toText().data().toInt();

    QString imageFilePath = characterNode.firstChildElement("image").toText().data();
    image.setFileName(imageFilePath);
}
