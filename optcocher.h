#ifndef OPTCOCHER_H
#define OPTCOCHER_H


#include <QList>
#include <QString>

#include "code.h"

class OptCocher
{
public:
    OptCocher();
    OptCocher(QString n);

    Code getCode(){return this->code;}

    void setCode(Code c){this->code = c;}


private:
    QString name;
    Code code;

};

#endif // OPTCOCHER_H
