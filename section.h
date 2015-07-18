#ifndef SECTION_H
#define SECTION_H

#include<QList>

#include "listderoul.h"
#include "optcocher.h"
#include "infochamp.h"

class Section
{
public:
    Section(int nbL, int nbO);//sert a mettre a jour le nombre d'elem de la section. (verififcation par rapport au xml)
    Section();

    QString getNameS(){return this->name;}
    QList<ListDeroul> getListeDeroul(){return this->listD;}
    QList<OptCocher> getOptCocher(){return this->listO;}
    QList<InfoChamp> getListInfoChamp(){return this->listInfoChamp;}


    void setNameS(QString n){this->name = n;}
    void setnbL(int nbL){this->nbListeD = nbL;}
    void setnbO(int nbO){this->nbOpt = nbO;}

    void setListesListDeroul(QList<ListDeroul> lD){this->listD = lD;}
    void setListesOptCocher(QList<OptCocher> lO){this->listO = lO;}
    void setListeInfoChamp(QList<InfoChamp> lI){this->listInfoChamp = lI;}
    QString resumeConf();//renvoie la configuration de la section
    Code findCodeOptCocher(QString name);//retourne le code de la section correspondant au nom en paramétre.
    Code findCodeListDeroul(QString sectionName, QString champValue);//retourne le code de la section correspondant au nom en paramétre.
    bool isEmptyListInfoChamp();//retourne true si au moins une infochamp de la liste d'infochamp a son attribut code actif =true.


private:
    QList<ListDeroul> listD;//liste des listes déroulantes de la section.
    QList<OptCocher> listO;//liste des options à cocher de la section.
    QList<InfoChamp> listInfoChamp;//cette liste servira pour l'affichage du résumé de la configuration.
                                  // il faudra transmettre cette liste au menus suivant pour l'afficher dans
                                  //le menu main section.


    QString name;
    int nbListeD;//représente le nombre de liste déroulante que la section doit contenir.
    int nbOpt;


    void addDeroul(ListDeroul elem);//ajoute un element a la liste déroulante
    void addOpt(OptCocher elem);//ajoute un element à la liste d'options a cocher

};

#endif // SECTION_H
