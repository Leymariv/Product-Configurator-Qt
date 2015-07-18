#include "mdo.h"

/*
 *Auteur: Valmon Leymarie
 *
 *
 *
 *Cette classe permet de gérer les données de la main d'oeuvre via la classe Data
 *
 */

Mdo::Mdo()
{
}

Mdo::Mdo(QString n, double f){
    this->name = n;
    this->coutH = f;

}
