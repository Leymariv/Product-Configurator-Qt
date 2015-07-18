#ifndef CODE_H
#define CODE_H

#include <QWidget>
#include <composant.h>
#include <composantaffaire.h>
#include <composantfg.h>
#include <operation.h>
#include <codet.h>

class Code
{
public:
    Code();

    QString getChamp(){return this->champName;}
    QString getCodeName(){return this->codeName;}
    int getPos(){return this->position;}
    QString getCodeVal(){return this->valeur;}
    QList<Composant> getListComp(){return this->listComp;}
    QList<Operation> getListOp(){return this->listOp;}
    QList<Codet> getListCodet(){return this->listCodet;}
    bool getActif(){return this->actif;}

    void setCodeVal(QString c){this->valeur = c;}
    void setChamp(QString n){this->champName = n;}
    void setCodeName(QString n){this->codeName = n;}
    void setPos(int p){this->position = p;}
    void setListComp(QList<Composant> l){this->listComp = l;}
    void setListOp(QList<Operation> l){this->listOp = l;}
    void setListCodet(QList<Codet> l){this->listCodet = l;}
    void setNomX(QString val);//Permet de mettre à jour la nomenclature du code lorsque la quantité est à x et réalise le calcul (2*x => 6 si x=3)
    void setActif(bool b){this->actif = b;}

private:
    QString champName;//Nom du champ relatif au code produit.
    int position;//position du code dans le code produit final
    QString valeur;//valeur du code ( voir codeProduit.xls pour le cde)
    QString codeName;//nom du code
    QList<Composant> listComp;//liste de tous les composants qu'implique le code
    QList<Operation> listOp;//liste de toutes les opérations qu'implique le code
    QList<Codet> listCodet;//liste de toutes les opérations qu'implique le code
    bool actif;//pour savoir si le code est utilisé ou non (option cochée, champ sélectionné).



};

#endif // CODE_H

