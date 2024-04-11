//
// Created by akhomchenko on 11.04.24.
//

#include "creature.h"
#include <QTextStream>

Creature::Creature(QString creatureName) {
    title = std::move(creatureName);
}

Creature::Creature(QFile *xmlConfig) {

}

Creature::~Creature() {

}

int Creature::loadCreatureFromFile(QFile *xmlConfigFile) {
    if(!xmlConfigFile->open(QIODevice::ReadWrite)){
        emit xmlSaveError(xmlConfigFile->errorString());
        return OpenFileError;
    }
    configDom.setContent(xmlConfigFile);
    xmlConfigFile->close();
    return ErrorNone;
}

int Creature::saveCreatureToFile(QString pathToXml) {
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
