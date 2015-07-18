#include "marche.h"

Marche::Marche()
{
    this->nomMarche = "";
}

Marche::Marche(QString name){
    this->nomMarche = name;
}

Codet Marche::findCodet(QString id){
    Codet c;

    if(!this->codetsList.isEmpty())
        for (int i = 0; i <this->codetsList.size() ; i++){
            c = this->codetsList.value(i);
            if(c.getId() == id){
                return c;
            }
        }
    c.setName("ERR");
    return c;
}
