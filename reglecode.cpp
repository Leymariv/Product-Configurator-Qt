#include "reglecode.h"

RegleCode::RegleCode()
{
    this->actif = false;
    this->message = "";
}

void RegleCode::setNomX(QString val){
    if(!this->listComp.isEmpty()){
        for (int i = 0; i<this->listComp.size(); i++){
            Composant *c = &(listComp.operator [](i));
            if(c->getQte().indexOf("x") != -1){
                int value = val.toInt();

                if(c->getQte() == "x"){
                    c->setQte(val);
                }

                else{
                    QString itg = c->getQte();
                    itg.truncate(1);//integer

                    if(itg =="x"){//si dans le xml on a écrit x+2 au lieu de 2+x
                        itg = c->getQte().right(2);
                    }
                    QString op = c->getQte();
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
                        value = value / integer +1;

                    c->setQte(QString::number(value));

                }
            }

        }

    }
}
