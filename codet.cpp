#include "codet.h"

Codet::Codet()
{
    this->codeArticle ="";
    this->name = "";
    this->quantite = "0";
    this->prixVenteU = 0;
    this->action="";
}

void Codet::setQteX(QString val){
    int value = val.toInt();
    if(this->getQte() == "x"){
        this->setQte(val);
    }

    else{
        QString itg = this->getQte();
        itg.truncate(1);//integer

        if(itg =="x"){//si dans le xml on a écrit x-2 au lieu de 2-x
            itg = this->getQte().right(1);
        }
        QString op = this->getQte();
        op = op.right(2);
        op = op.left(1);//operande +,-,*,∕

        int integer = itg.toInt();

        if(op == "*")
            value = value*integer;
        if(op == "+")
            value = value+integer;
        if(op == "-")
            value = value - integer;
        if(op == "/")
            value = value / integer;

        this->quantite = QString::number(value);

    }
}

