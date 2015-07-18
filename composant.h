#ifndef COMPOSANT_H
#define COMPOSANT_H

#include <QtPlugin>
#include <QWidget>
#include <iostream>
#include <string>

class Composant
{
public:
    Composant();

    double getPrixU(){return this->prixU;}
    QString getName(){return this->name;}
    QString getType(){return this->type;}
    QString getQte(){return this->quantite;}
    QString getAction(){return this->action;}
    QString getRef(){return this->ref;}
    QString getFournisseur(){return this->fournisseur;}
    QString getId(){return this->id;}

    void setFournisseur(QString f){this->fournisseur = f;}
    void setRef(QString r){this->ref = r;}
    void setPrixU(double p){this->prixU = p;}
    void setName(QString n){this->name = n;}
    void setQte(QString q){this->quantite = q;}
    void setAction(QString a){this->action = a;}
    void setId(QString a){this->id = a;}

protected:
    double prixU;//prix unitaire
    QString name;
    QString type;//composantFG ou composantAffaire
    QString quantite;
    QString action;//add ou remove
    QString ref;
    QString fournisseur;
    QString id;//id du composant

};

Q_DECLARE_INTERFACE(Composant, "Configurator.Interface/1.0")

#endif // COMPOSANT_H



