#ifndef INFOCHAMP_H
#define INFOCHAMP_H

#include <QString>
#include "code.h"
#include "codet.h"

class InfoChamp
{
public:
    InfoChamp();
    InfoChamp(QString n,QString v,QString t);

    QString getNomChamp(){return this->nomChamp;}
    QString getValChamp(){return this->valChamp;}
    QString getTypeChamp(){return this->typeChamp;}
    Code getCode(){return this->code;}

    void setNomChamp(QString nC){this->nomChamp = nC;}
    void setValChamp(QString vC){this->valChamp = vC;}
    void setTypeChamp(QString tC){this->typeChamp = tC;}
    void setCode(Code c){this->code = c;}

private:
    QString nomChamp;
    QString valChamp;
    QString typeChamp;

    Code code;

};

#endif // INFOCHAMP_H

