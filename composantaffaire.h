#ifndef COMPOSANTAFFAIRE_H
#define COMPOSANTAFFAIRE_H

#include "composant.h"

class ComposantAffaire: public Composant
{
    Q_INTERFACES(Composant)

public:
    ComposantAffaire();
    ComposantAffaire(double p,QString n);

    void setRefFournisseur(QString r){this->refFournisseur = r;}
    void setFournisseur(QString f){this->fournisseur = f;}

    QString getRefFournisseur(){return this->refFournisseur;}
    QString getFournisseur(){return this->fournisseur;}



protected:
    QString refFournisseur;

};

#endif // COMPOSANTAFFAIRE_H
