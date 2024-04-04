//
// Created by arsen on 01.04.2024.
//

#ifndef DM_ASSIST_DNDCREATURE_H
#define DM_ASSIST_DNDCREATURE_H

#include <QString>
#include <QFile>
#include <QPixmap>
#include <QMap>
#include <QDomDocument>
#include <QApplication>

class dndCreature : public QObject{
Q_OBJECT
public:
    explicit dndCreature(QString creatureName);
    explicit dndCreature(QFile *xmlConfig);

    ~dndCreature();

    int loadCreatureFromFile(QFile *xmlConfigFile = nullptr);
    int saveCreatureToFile(QDomDocument configDomDocument, QString pathToXml = QCoreApplication::applicationDirPath());

    static int getBonuseFromCharacteristic(int characteristicValue);
    int getCharacterSheetId() const {return id;};
    QString getTitle() const {return title;};
    int getAc() const {return ac;};
    int getHp() const {return hp;};
    int getMaxHp() const {return maxHP;};
    int getInitiativeBonus() const {return initiativeBonus;};

    void setMaxHp(int value);
    bool setHp(int value);

    enum FileErrors{
        ErrorNone = 0,
        OpenFileError = -1,
        ParseFileError = -2
    };
signals:
    void titleChanged();
    void xmlLoadError(QString errString);
    void xmlSaveError(QString errString);
    void imageChanged();
    void maxHpCahged();

protected:
    int id; ///< Unique id of charlist

    QString title;
    QString notes;

    QPixmap image;

    // Characteristics
    QMap<QString, int> characteristics;

    int initiativeBonus = 0;

    int ac = 10;
    int maxHP = 0;
    int hp = 0;
    QString hpFormula = "";

    QMap<QString, int> speedValues;

    QDomDocument configDom;
};


#endif //DM_ASSIST_DNDCREATURE_H
