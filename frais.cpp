#include "frais.h"

/*
 *Auteur: Valmon Leymarie
 *
 *
 *
 *Cette classe permet de gérer les frais (DSS, de direction...) via la classe Data
 *
 */
Frais::Frais(){

}

Frais::Frais(QString n, double f)
{
    this->name = n;
    this->pourcentage =f;
}
