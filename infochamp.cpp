#include "infochamp.h"

InfoChamp::InfoChamp()
{
}

InfoChamp::InfoChamp(QString n, QString v, QString t){
    this->nomChamp = n;
    this->typeChamp = t;
    this->valChamp = v;
}
