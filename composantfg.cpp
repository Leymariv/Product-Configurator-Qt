#include "composantfg.h"

ComposantFG::ComposantFG():Composant()
{
    this->type = "composantFG";
}


ComposantFG::ComposantFG(double p, QString n){
    this->prixU = p;
    this->name = n;
    this->type = "composantFG";
}
