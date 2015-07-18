#include "section.h"

Section::Section()
{
}

Section::Section(int nbL, int nbO){

    this->nbListeD = nbL;
    this->nbOpt = nbO;
}

QString Section::resumeConf(){
    QString resumeConf="";
    if(!this->getListInfoChamp().isEmpty()){
        for(int i = 0; i < this->getListInfoChamp().size();i++){
            if(this->getListInfoChamp().value(i).getValChamp() == "oui"){


                resumeConf += "<p><span style=\"font-size:11pt;\"> -"+this->getListInfoChamp().value(i).getNomChamp()+
                        ": \u2611</span></p>";
            }
            else if(this->getListInfoChamp().value(i).getValChamp() == "non"){

                //    resumeConf += "<p><span style=\"font-size:11pt;\"> - "+this->getListInfoChamp().value(i).getNomChamp()+
                //      ": \u2612</span></p>";
            }
            else{
                resumeConf += "<p><span style=\"font-size:11pt;\"> - "+this->getListInfoChamp().value(i).getNomChamp()+
                        ": "+this->getListInfoChamp().value(i).getValChamp()+"</span></p>";
            }
        }
    }
    return resumeConf;
}


bool Section::isEmptyListInfoChamp(){
    for (int i = 0; i< this->getListInfoChamp().size() ;i++){
        if(this->getListInfoChamp().value(i).getCode().getActif() == true){
            return false;
        }
    }
    return true;
}

Code Section::findCodeOptCocher(QString name){
    Code c;
    if(!this->getOptCocher().isEmpty()){
        for (int k = 0; k < this->getOptCocher().size(); k++){
            c = this->getOptCocher().value(k).getCode();
            if(c.getChamp() == name){
                return c;
            }
        }
    }
    c.setCodeName("ERR");
    return c;
}

Code Section::findCodeListDeroul(QString sectionName,QString champValue){
    Code c;
    if(!this->getListeDeroul().isEmpty()){
        for (int k = 0; k < this->getListeDeroul().size(); k++){
            if(this->getListeDeroul().value(k).getName() == sectionName){
                for (int i = 0; i < this->getListeDeroul().value(k).getListCode().size(); i++){
                    c = this->getListeDeroul().value(k).getListCode().value(i);
                    if(c.getChamp() == champValue){
                        return c;
                    }
                }
            }
        }
    }
    c.setCodeName("ERR");
    return c;
}
