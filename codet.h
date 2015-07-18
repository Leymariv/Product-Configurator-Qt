#ifndef CODET_H
#define CODET_H

#include <QWidget>

class Codet
{
public:
    Codet();

    void setName(QString n){this->name = n;}
    void setCodeArticle(QString c){this->codeArticle = c;}
    void setPrixVenteU(double p){this->prixVenteU = p;}
    void setQte(QString q){this->quantite = q;}
    void setAction(QString a){this->action = a;}
    void setQteX(QString val);//sert à gérer les quantités de types 3+x
    void setId(QString a){this->id = a;}

    QString getName(){return this->name;}
    QString getCodeArticle(){return this->codeArticle;}
    double getPrixVenteU(){return this->prixVenteU;}
    QString getQte(){return this->quantite;}
    QString getAction(){return this->action;}
    QString getId(){return this->id;}

private:

    QString name;//nom du codet
    QString codeArticle;//code article du codet
    double prixVenteU;//prix de vente unitaire du codet
    QString quantite;//quantité du codet.
    QString action;//"remove" ou "add" la quantité de codet
    QString id;//id du codet
};

#endif // CODET_H
