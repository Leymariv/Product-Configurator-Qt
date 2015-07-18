#ifndef REGLECODE_H
#define REGLECODE_H

#include <QWidget>
#include "composant.h"
#include "composantaffaire.h"
#include "composantfg.h"
#include "operation.h"
#include "codet.h"

class RegleCode
{
public:
    RegleCode();

    QString getName(){return this->name;}
    QString getCode1(){return this->code1;}
    QString getCode2(){return this->code2;}
    QString getOperande(){return this->operande;}
    QString getMessage(){return this->message;}
    QString getOperation(){return this->operation;}
    QString getNombre(){return this->nombre;}
    QString getComparaison(){return this->comparaison;}
    QString getRegleType(){return this->regleType;}
    QList<Composant> getListComp(){return this->listComp;}
    QList<Operation> getListOperation(){return this->listOperation;}
    QList<Codet> getListCodet(){return this->listCodet;}
    bool getActif(){return this->actif;}

    void setName(QString c){this->name = c;}
    void setCode1(QString c){this->code1 = c;}
    void setCode2(QString c){this->code2 = c;}
    void setOperande(QString c){this->operande = c;}
    void setOperation(QString c){this->operation = c;}
    void setNombre(QString c){this->nombre = c;}
    void setMessage(QString c){this->message = c;}
    void setComparaison(QString c){this->comparaison = c;}
    void setRegleType(QString c){this->regleType = c;}
    void setListComp(QList<Composant> l){this->listComp = l;}
    void setListOperation(QList<Operation> l){this->listOperation = l;}
    void setListCodet(QList<Codet> l){this->listCodet = l;}
    void setActif(bool b){this->actif = b;}

    void setNomX(QString val);

private:

    QString name;
    QString code1;
    QString code2;
    QString nombre;//sert a stocké le nombre a comparer ou le résultat d'une régle d'opération

    //stockent le type d'opération entre les 2 codes ou code et nombre
    QString operande;
    QString comparaison;
    QString operation;

    QString regleType;//type de régle:OPERANDE, OPERATION, COMPCODE, COMPNBR
    QString message;

    QList<Composant> listComp;
    QList<Operation> listOperation;
    QList<Codet> listCodet;
    bool actif;

};

#endif // REGLECODE_H
