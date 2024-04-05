//
// Created by arsen on 01.04.2024.
//

#include "dndcreature.h"
#include <utility>
#include <QTextStream>

dndCreature::dndCreature(QString creatureName) {
    title = std::move(creatureName);
}

dndCreature::dndCreature(QFile *xmlConfig) {
}

dndCreature::~dndCreature() {

}

/**
 * Load creature stat list to DOM document object
 * @param xmlConfigFile .xml, contains stat list of creature
 * @return error code
 */
int dndCreature::loadCreatureFromFile(QFile *xmlConfigFile) {
    if(!xmlConfigFile->open(QIODevice::ReadWrite)){
        emit xmlSaveError(xmlConfigFile->errorString());
        return OpenFileError;
    }
    configDom.setContent(xmlConfigFile);
    xmlConfigFile->close();
    return ErrorNone;
}

/**
 * Save DOM document object, contains stats of creature to .xml file
 * @param pathToXml string with path to .xml file
 * @return error code
 */
int dndCreature::saveCreatureToFile(QString pathToXml) {
    QString configFileNamePath;
    if(pathToXml == QCoreApplication::applicationDirPath()){
        configFileNamePath = pathToXml + "/configs/" + id + "_charlist.xml";
    } else
    {
        configFileNamePath = pathToXml;
    }
    QFile config(configFileNamePath);

    if (!config.open(QFile::WriteOnly))
    {
        emit xmlLoadError(config.errorString());
        return OpenFileError;
    }

    QTextStream xmlContent(&config);
    xmlContent << configDom.toString();
    return ErrorNone;
}

int dndCreature::getBonuseFromCharacteristic(int characteristicValue) {
    return (characteristicValue >= 0) ? (characteristicValue / 10) : (characteristicValue - 10 + 1) / 10;
}

void dndCreature::setMaxHp(int value) {
    maxHP = value;
    if (hp > maxHP)
        hp = maxHP;
    emit maxHpCahged();
}

bool dndCreature::setHp(int value) {
    if(value <= maxHP){
        hp = value;
        return true;
    } else
        return false;
}

void dndCreature::setFullHp() {
    hp = maxHP;
}

void dndCreature::doDamage(int hpValue) {
    hp -= hpValue;
    if (hp < 0)
        hp = 0;
}
