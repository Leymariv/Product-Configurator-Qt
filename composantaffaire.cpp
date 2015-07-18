#include "composantaffaire.h"

ComposantAffaire::ComposantAffaire():Composant()
{
    this->type = "composantAffaire";
}


ComposantAffaire::ComposantAffaire(double p, QString n){
    this->prixU = p;
    this->name = n;
    this->type = "composantAffaire";
}
