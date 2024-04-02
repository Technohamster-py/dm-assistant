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

int dndCreature::loadCreatureFromFile(QFile *xmlConfigFile) {
    if(!xmlConfigFile->open(QIODevice::ReadWrite)){
        return OpenFileError;
    }
    configDom.setContent(xmlConfigFile);
    xmlConfigFile->close();
    return ErrorNone;
}

dndCreature::~dndCreature() {

}

int dndCreature::saveCreatureToFile(QDomDocument configDomDocument, QString pathToXml) {
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
        return OpenFileError;
    }

    QTextStream xmlContent(&config);
    xmlContent << configDomDocument.toString();
    return ErrorNone;
}

int dndCreature::getBonuseFromCharacteristic(int characteristicValue) {
    return (characteristicValue >= 0) ? (characteristicValue / 10) : (characteristicValue - 10 + 1) / 10;
}
