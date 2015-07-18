#ifndef OPERATION_H
#define OPERATION_H

#include <QWidget>

class Operation
{
public:
    Operation();

    double getCoutHoraireTot(){return this->coutHoraireTot;}
    QString getName(){return this->name;}
    QString getId(){return this->id;}
    QString getQte(){return this->quantite;}
    QString getAction(){return this->action;}
    double getNbHCdp(){return this->nbHCdp;}
    double getNbHTech(){return this->nbHTech;}
    double getNbHOuv(){return this->nbHOuv;}

    void setCoutHoraireTot(double p){this->coutHoraireTot = p;}
    void setName(QString n){this->name = n;}
    void setId(QString n){this->id = n;}
    void setQte(QString q){this->quantite = q;}
    void setAction(QString a){this->action = a;}
    void setNbHCdp(double c){this->nbHCdp = c;}
    void setNbHTech(double t){this->nbHTech = t;}
    void setNbHOuv(double o){this->nbHOuv = o;}

private:
    double coutHoraireTot;//Cout horaire total
    double nbHOuv;//nombre d'heures pour un ouvrier
    double nbHCdp;//nombre d'heures pour un cdp
    double nbHTech;//nombre d'heures pour un tech
    QString name;
    QString id;//id de l'opération
    QString quantite;
    QString action;//add ou remove
};

#endif // OPERATION_H
