#ifndef MARCHE_H
#define MARCHE_H

#include "codet.h"
#include <QWidget>

class Marche
{
public:
    Marche();
    Marche(QString name);
    QString getName(){return this->nomMarche;}
    QList<Codet> getCodetsList(){return this->codetsList;}
    QList<Codet> getBaseCommuneCodets(){return this->baseCommuneCodets;}

    void setName(QString n){this->nomMarche = n;}
    void setCodetList(QList<Codet> l){this->codetsList = l;}
    void setBaseCommuneCodets(QList<Codet> l){this->baseCommuneCodets = l;}

     Codet findCodet(QString id);//renvoie un codet de la liste des codets

private:
    QString nomMarche;// nom du marché (ERDF,RTE..Etc)
    QList<Codet> codetsList;//liste des codets du marché.
    QList<Codet> baseCommuneCodets;//liste de tous les codets de la base commune.
};

#endif // MARCHE_H
