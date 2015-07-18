#ifndef FRAIS_H
#define FRAIS_H

#include <QWidget>

class Frais
{
public:
    Frais();
    Frais(QString n, double f);

    QString getName(){return this->name;}
    double getPourcentage(){return this->pourcentage;}

    void setName(QString s){this->name = s;}
    void setPourcentage(double f){this->pourcentage = f;}


private:
    QString name;
    double pourcentage;

};

#endif // FRAIS_H
