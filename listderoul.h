#ifndef LISTDEROUL_H
#define LISTDEROUL_H

#include <QList>
#include <QString>

#include "code.h"

class ListDeroul
{
public:
    ListDeroul();

    ListDeroul(QString n);

    void setNameL(QString n){this->name = n;}

    void setTypeChamp(QString tC){this->typeChamp = tC;}
    void setListCode(QList<Code> lC){this->listCode = lC;}
    void setGenerique(bool b){this->generique = b;}

    QString getName(){return this->name;}
    QString getTypeChamp(){return this->typeChamp;}
    QList<Code> getListCode(){return this->listCode;}
    bool getGenerique(){return generique;}

private:
    QString name;
    QList<Code> listCode;//Pour une liste déroulante ou les champs on une nomenclature commune
                          //cf CDE "codeRP48TS48V" les composants commun seront présents dans chaque champs de la liste

    QString typeChamp;
    bool generique;
};

#endif // LISTDEROUL_H
