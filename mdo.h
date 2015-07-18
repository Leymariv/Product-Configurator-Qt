#ifndef MDO_H
#define MDO_H

#include <QWidget>

class Mdo
{
public:
    Mdo();
     Mdo(QString n, double f);

    QString getName(){return this->name;}
    double getCoutH(){return this->coutH;}

    void setName(QString s){this->name = s;}
    void setCoutH(double f){this->coutH = f;}


private:
    QString name;
    float coutH;

};

#endif // MDO_H
