#ifndef COMPOSANTFG_H
#define COMPOSANTFG_H

#include "composant.h"

class ComposantFG: public Composant
{
    Q_INTERFACES(Composant)

public:
    ComposantFG();
    ComposantFG(double p,QString n);

    void setRefFG(QString r){this->refFG = r;}
    QString getRefFG(){return this->refFG;}

protected:
    QString refFG;
};

#endif // COMPOSANTFG_H
