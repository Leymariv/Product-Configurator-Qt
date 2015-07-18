/*
     *Auteur: Valmon Leymarie
     *
     *
     *
     *Classe de définition de l'objet produit. Cet objet sera instancié plusieurs fois  pour être ajouté a la liste
     * des produits de la classe DATA.
     *
     *
     */

#include "produit.h"

Produit:: Produit(){
    this->nbSection = 0;
    this->prixTotNomFG = 0;
    this->prixTotNomAffaire = 0;
    this->prixTotMdo = 0;
    this->nbHCdp = 0;
    this->nbHOuv = 0;
    this->nbHTech = 0;
    this->qte=1;
    this->prixVenteMarche = 0;
}

Produit:: Produit(QString n, QString i, QString p, QString t)
{
    this->qte=1;
    this->lienImg = i;
    this->lienPdf = p;
    this->name = n;
    this->text = t;
    this->nbHCdp = 0;
    this->nbHOuv = 0;
    this->nbHTech = 0;
    this->nbSection = 0;
    this->prixTotNomFG = 0;
    this->prixTotNomAffaire = 0;
    this->prixTotMdo = 0;
    this->prixVenteMarche = 0;
}

QString Produit::affichInfos(){

    QString infos ="";
    infos += "Name: "+this->getName()+"\n\n Lien PDF: "+this->getLienPdf()+ "\n\n Lien IMG: "+this->getLienImg()+"";
    if (this->getNbSection()==0) return infos;
    for(int i = 0; i < this->getNbSection(); i++){
        infos +="\n\nSection"+QString::number(i)+": ";
        infos +="Name: "+this->getListeSection().takeAt(i).getNameS();
        if(this->getListeSection().takeAt(i).getListeDeroul().size() != 0){
            for (int p =0 ; p< this->getListeSection().takeAt(i).getListeDeroul().size();p++ ){
                infos+= "\n Liste Déroulante"+QString::number(p)+" Name: "+
                        this->getListeSection().takeAt(i).getListeDeroul().takeAt(p).getName();
                infos+="\n Champs:";
                if(this->getListeSection().takeAt(i).getListeDeroul().takeAt(p).getListCode().size() !=0){
                    for(int k=0; k< this->getListeSection().takeAt(i).getListeDeroul().takeAt(p).getListCode().size() ; k++){
                        infos+="\n"+this->getListeSection().takeAt(i).getListeDeroul().takeAt(p).getListCode().takeAt(k).getChamp();
                    }
                }
            }
        }
        if(this->getListeSection().takeAt(i).getOptCocher().size() != 0){
            for (int p =0 ; p< this->getListeSection().takeAt(i).getOptCocher().size();p++ ){
                infos+= "\n Option à cocher"+QString::number(p)+" Name: "+this->getListeSection().takeAt(i).
                        getOptCocher().takeAt(p).getCode().getChamp();

            }
        }
    }
    return infos;
}

QString Produit::resumeConfNormale(){
    QString resumeConf="";
    if(!this->getListeSection().isEmpty()){
        for (int p = 0; p < this->getListeSection().size(); p++){
            Section section = this->getListeSection().value(p);
            QString color="";
            if(section.resumeConf() !="")//section traitée
                color = "#FE920C";
            else                         //section non traitée
                color = "#5d5d5d";
            resumeConf += "<html><head/><body><p align=\"left\"><span style=\" font-size:12pt; font-weight:600; color:"+color+";\">\u2022"
                    +section.getNameS()+"</span></p>";
            resumeConf += section.resumeConf();
            resumeConf += "</body></html>";
        }
        return resumeConf;
    }
    else{

        return "ERROR produit.cpp";
    }
}

QString Produit::resumeConfBordereau(){
    QString resumeConf="";
    prixVenteMarche =0;
    resumeConf += "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">"
            +this->getCurrentMarche().getName()+"\n</span></p>";
    for(int i=0 ; i < this->getListCodets().size(); i++){
        Codet c = this->getListCodets().value(i);
        double prix = (c.getQte().toDouble())*c.getPrixVenteU();
        if(c.getQte().toInt(0,10)!=0){
        resumeConf += "<p><span style=\"font-size:13pt;\"> \u2022 "+c.getQte()+
                " "+c.getName()+" - ("+c.getCodeArticle()+") : "
                +QString::number(prix)+"€\n</span></p>";
        prixVenteMarche += prix;
        }
    }
    resumeConf += "<p align=\"right\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\"> Prix de Vente : "+
            QString::number(prixVenteMarche)+"€ </span></p></body></html>";
    return resumeConf;
}

QString Produit::resumeNomenclature(){
    this->prixTotNomFG = 0;
    this->prixTotNomAffaire = 0;
    QString resumeNom="";
    if(!this->getBaseCommuneComposants().isEmpty()){ //Affichage composants base commune + calcul prix total
        resumeNom +="Base Commune\n";
        for (int p = 0; p< this->getBaseCommuneComposants().size(); p++){
            Composant c = this->getBaseCommuneComposants().value(p);
            double prixComp = c.getPrixU()*
                    (c.getQte().toDouble());
            resumeNom += "+ "+c.getQte()+
                    c.getName()+" : +"
                    +QString::number(prixComp)+" "
                    +"€\n";
            if(c.getType() == "composantFG"){
                this->listComposantFG.append(c);
                prixTotNomFG += prixComp;
            }
            else{
                this->listComposantAffaire.append(c);
                prixTotNomAffaire += prixComp;
            }
        }
    }

    if(!this->getListeSection().isEmpty()){//affichage composants configuration sans les régles + calcul prix total
        for (int p = 0; p < this->getListeSection().size(); p++){
            Section section = this->getListeSection().value(p);
            if(!section.isEmptyListInfoChamp()){//si au moins une infochamp est active.
                resumeNom += "\n"+section.getNameS()+"\n";

                for (int i = 0; i < section.getListInfoChamp().size(); i++){
                    InfoChamp infoChamp = section.getListInfoChamp().value(i);
                    for (int k = 0; k < infoChamp.getCode().getListComp().size(); k++){
                        Composant c = infoChamp.getCode().getListComp().value(k);
                        double prixComp = c.getPrixU()*(c.getQte().toDouble());

                        QString operand = (c.getAction() == "add") ? "+" : "-";
                        resumeNom += operand+" "+c.getQte()+" "+c.getName()+
                                " : "+operand+QString::number(prixComp)+"€\n";

                        if(c.getType() == "composantFG"){
                            this->listComposantFG.append(c);
                            if(operand == "+")
                                prixTotNomFG += prixComp;
                            else
                                prixTotNomFG -=prixComp;
                        }
                        else{
                            this->listComposantAffaire.append(c);
                            if(operand == "+")
                                prixTotNomAffaire += prixComp;
                            else
                                prixTotNomAffaire -=prixComp;
                        }
                    }
                }
            }
        }
    }

    if(!this->getListRegle().isEmpty()){//affichage composants issus des régles + calcul prix total
        resumeNom +="\nRégles de Nomenclature\n\n";
        for (int i = 0; i< this->getListRegle().size();i++){
            RegleCode r = this->getListRegle().value(i);

            if(r.getActif()){//si la régle est valable ( la condition entre les codes est vérifiée)
                for(int k =0;k <r.getListComp().size();k++){
                    Composant c = r.getListComp().value(k);
                    double prixComp = c.getPrixU()*(c.getQte().toDouble());
                    QString operand = (c.getAction() == "add") ? "+" : "-";
                    resumeNom += operand+" "+c.getQte()+" "+c.getName()+
                            " : "+operand+QString::number(prixComp)+"€\n";

                    if(c.getType() == "composantFG"){
                        this->listComposantFG.append(c);
                        if(operand == "+")
                            prixTotNomFG += prixComp;
                        else
                            prixTotNomFG -=prixComp;
                    }
                    else{
                        this->listComposantAffaire.append(c);
                        if(operand == "+")
                            prixTotNomAffaire += prixComp;
                        else
                            prixTotNomAffaire -=prixComp;
                    }
                }
            }

        }

    }
    mergeLists();

    return resumeNom;
}

void Produit::mergeLists(){
    for(int i = 0;i<this->listComposantFG.size();i++){
        Composant c1 = this->listComposantFG.value(i);
        for(int j = 0 ;j<this->listComposantFG.size();j++){
            Composant c2 = this->listComposantFG.value(j);
            if(c1.getName() == c2.getName()&& i!=j){
                int qt1 = c1.getQte().toInt(0,10);
                int qt2 = c2.getQte().toInt(0,10);
                if(c2.getAction() == "remove"){
                    c1.setQte(QString::number(qt1-qt2));
                }
                else{
                    c1.setQte(QString::number(qt1+qt2));
                }
                listComposantFG.replace(i,c1);
                listComposantFG.removeAt(j);
                j--;
            }
        }
    }
    for(int i = 0;i<this->listComposantAffaire.size();i++){
        Composant c1 = this->listComposantAffaire.value(i);
        for(int j = 0 ;j<this->listComposantAffaire.size();j++){
            Composant c2 = this->listComposantAffaire.value(j);
            if(c1.getName() == c2.getName() && i!=j){
                int qt1 = c1.getQte().toInt(0,10);
                int qt2 = c2.getQte().toInt(0,10);
                if(c2.getAction() == "remove"){
                    c1.setQte(QString::number(qt1-qt2));
                }
                else{
                    c1.setQte(QString::number(qt1+qt2));
                }
                listComposantAffaire.replace(i,c1);
                listComposantAffaire.removeAt(j);
                j--;
            }
        }
    }
    for(int i = 0;i<this->listCodet.size();i++){
        Codet c1 = this->listCodet.value(i);
        for(int j = 0 ;j<this->listCodet.size();j++){
            Codet c2 = this->listCodet.value(j);
            if(c1.getName() == c2.getName() && i!=j){
                int qt1 = c1.getQte().toInt(0,10);
                int qt2 = c2.getQte().toInt(0,10);
                if(c2.getAction() == "remove"){
                    c1.setQte(QString::number(qt1-qt2));
                }
                else{
                    c1.setQte(QString::number(qt1+qt2));
                }
                listCodet.replace(i,c1);
                listCodet.removeAt(j);
                j--;
            }
        }
    }

}


void Produit::majRegles(int indice){//assez compliqué à coder du fait que je veux pouvoir récupérer
    //le booléen "actif" d'un objet "Code" ou d'un objet "Regle"
    if(!this->getListRegle().isEmpty()){
        for (int i = 0; i< this->getListRegle().size();i++){
            RegleCode r = this->getListRegle().value(i);
            Code c1 = this->findCodeInfoChamp(r.getCode1());
            Code c2 = this->findCodeInfoChamp(r.getCode2());
            if(r.getRegleType() == "OPERANDE"){//regle de type operande
                RegleCode r1;
                RegleCode r2;

                bool b1 = c1.getActif();
                bool b2= c2.getActif();

                if (c1.getCodeName() == "ERR"){//si le code n'a pas été récupéré, c'est une régle
                    r1 = findRegle(r.getCode1());
                    b1 = r1.getActif();
                }
                else{//mise a jour de la nomenclature pour une régle du type
                    //<regle name="rg3" code1="CodeALi" operande="ET" code2="codeQLiPP5">
                    //<Composant id="28"  action="add" quantité="x"/>
                    //</regle>
                    r.setNomX(c2.getChamp());
                }
                if (c2.getCodeName() == "ERR"){
                    r2 = findRegle(r.getCode2());
                    b2 = r2.getActif();
                }
                else{//mise a jour de la nomenclature pour une régle du type coffretITI/NOMENCLATURE
                    //<regle name="rg3" code1="CodeALi" operande="ET" code2="codeQLiPP5">
                    //<Composant id="28"  action="add" quantité="x"/>
                    //</regle>
                    r.setNomX(c2.getChamp());
                }

                if(r.getOperande() == "AND"){
                    if(b1 && b2){
                        r.setActif(true);
                    }
                    else
                        r.setActif(false);
                }
                else if(r.getOperande() == "NOT AND") {
                    if(!b1 || b2){
                        r.setActif(true);
                    }
                    else
                        r.setActif(false);
                }
                else if(r.getOperande() == "AND NOT") {
                    if(b1 || !b2){
                        r.setActif(true);
                    }
                    else
                        r.setActif(false);
                }
                else if(r.getOperande() == "NOT AND NOT") {
                    if(!b1 || !b2){
                        r.setActif(true);
                    }
                    else
                        r.setActif(false);
                }

                else if(r.getOperande() == "OR") {
                    if(b1 || b2){
                        r.setActif(true);
                    }
                    else
                        r.setActif(false);
                }
                else if(r.getOperande() == "NOT OR") {
                    if(!b1 || b2){
                        r.setActif(true);
                    }
                    else
                        r.setActif(false);
                }
                else if(r.getOperande() == "OR NOT") {
                    if(b1 || !b2){
                        r.setActif(true);
                    }
                    else
                        r.setActif(false);
                }
                else if(r.getOperande() == "NOT OR NOT") {
                    if(!b1 || !b2){
                        r.setActif(true);
                    }
                    else
                        r.setActif(false);
                }

            }

            if(r.getRegleType() == "OPERATION"){//regle de type simple opération

                int value1 = c1.getCodeVal().toInt();
                int value2 = c2.getCodeVal().toInt();
                RegleCode r1,r2;
                if (c1.getCodeName() == "ERR"){//si le code n'a pas été récupéré, c'est une régle
                    r1 = findRegle(r.getCode1());
                    value1 = r1.getNombre().toInt();
                }
                if (c2.getCodeName() == "ERR"){//si le code n'a pas été récupéré, c'est une régle
                    r2 = findRegle(r.getCode2());
                    value2 = r2.getNombre().toInt();
                }

                if(r.getOperation()=="+"){
                    r.setNombre(QString::number(value1+value2));
                }
                if(r.getOperation()=="*"){

                    r.setNombre(QString::number(value1*value2));
                }
                if(r.getOperation()=="-"){

                    r.setNombre(QString::number(value1-value2));
                }
                if(r.getOperation()=="/"){

                    r.setNombre(QString::number(value1/value2 +1));
                }
            }
            if(r.getRegleType() == "COMPCODE"){//regle de type comparaison entre valeurs de codes
                int value1 = c1.getCodeVal().toInt();
                int value2 = c2.getCodeVal().toInt();

                if(r.getComparaison()=="EGAL"){
                    if(value1==value2)
                        r.setActif(true);
                    else
                        r.setActif(false);
                }
                if(r.getOperation()=="SUP"){
                    if(value1 > value2)
                        r.setActif(true);
                    else
                        r.setActif(false);
                }
                if(r.getOperation()=="INF"){

                    if(value1 < value2)
                        r.setActif(true);
                    else
                        r.setActif(false);
                }
            }
            if(r.getRegleType() == "COMPNBR"){//regle de type comparaison avec un nombre
                int value1 = c1.getCodeVal().toInt();
                int value2 = r.getNombre().toInt();
                RegleCode r1;

                if (c1.getCodeName() == "ERR"){//si le code n'a pas été récupéré, c'est une régle
                    r1 = findRegle(r.getCode1());
                    value1 = r1.getNombre().toInt();
                }

                if(r1.getName() == "ERR" && c1.getCodeName() == "ERR"){//si le code n'est ni une régle, ni un code, c'est qu'il n'a pas été utilisé, on return
                    r.setActif(false);
                }
                else{//sinon on fait les comparaisons
                    if(r.getComparaison()=="EGAL"){
                        if(value1==value2)
                            r.setActif(true);
                        else
                            r.setActif(false);
                    }
                    if(r.getComparaison()=="SUP"){
                        if(value1 > value2)
                            r.setActif(true);
                        else
                            r.setActif(false);
                    }
                    if(r.getComparaison()=="INF"){

                        if(value1 < value2)
                            r.setActif(true);
                        else
                            r.setActif(false);
                    }
                }
            }
            QList<RegleCode> rList = this->getListRegle();
            rList.replace(i,r);
            this->setListRegle(rList);
        }

        if(indice <1){
            this->majRegles(1);
        }
    }
}

Marche Produit::findMarche(QString s){
    Marche m;
    if(!this->getListMarche().isEmpty()){
        for(int i = 0 ; i<this->getListMarche().size();i++){
            m = this->getListMarche().value(i);
            if(m.getName() == s){
                return m;
            }
        }
    }
    m.setName("ERR");
    return m;
}

QString Produit :: resumeMdo(){
    prixTotMdo = 0;
    QString resumeNom="";
    if(!this->getBaseCommuneOperations().isEmpty()){ //Affichage opération base commune + calcul prix total
        resumeNom +="Base Commune\n";
        for (int p = 0; p< this->getBaseCommuneOperations().size(); p++){
            this->nbHCdp += this->baseCommuneOperations.value(p).getNbHCdp();//mise à jour de la somme des opérations de cdp
            this->nbHTech += this->baseCommuneOperations.value(p).getNbHTech();//mise à jour de la somme des opérations de tech
            this->nbHOuv += this->baseCommuneOperations.value(p).getNbHOuv();//mise à jour de la somme des opérations d' ouvrier

            double prixOp = this->getBaseCommuneOperations().value(p).getCoutHoraireTot()*
                    (this->getBaseCommuneOperations().value(p).getQte().toDouble());
            resumeNom += "+ "+this->getBaseCommuneOperations().value(p).getQte()+
                    this->getBaseCommuneOperations().value(p).getName()+" : +"
                    +QString::number(prixOp)+" "
                    +"€\n";
            prixTotMdo += prixOp;
        }
    }

    if(!this->getListeSection().isEmpty()){//affichage opérations issus des codes produits, configuration sans les régles + calcul prix total
        resumeNom += "\n Configuration\n";
        for (int p = 0; p < this->getListeSection().size(); p++){
            Section section = this->getListeSection().value(p);
            if(!section.isEmptyListInfoChamp()){//si au moins une infochamp est active.
                for (int i = 0; i < section.getListInfoChamp().size(); i++){
                    InfoChamp infoChamp = section.getListInfoChamp().value(i);
                    for (int k = 0; k < infoChamp.getCode().getListOp().size(); k++){
                        Operation op = infoChamp.getCode().getListOp().value(k);

                        this->nbHCdp += op.getNbHCdp();//mise à jour de la somme des opérations de cdp
                        this->nbHTech += op.getNbHTech();//mise à jour de la somme des opérations de tech
                        this->nbHOuv += op.getNbHOuv();//mise à jour de la somme des opérations d' ouvrier

                        double prixOp = op.getCoutHoraireTot()*(op.getQte().toDouble());

                        QString operand = (op.getAction() == "add") ? "+" : "-";
                        resumeNom += operand+" "+op.getQte()+" "+op.getName()+
                                " : "+operand+QString::number(prixOp)+"€\n";
                        if(operand == "+")
                            prixTotMdo += prixOp;
                        else
                            prixTotMdo -=prixOp;
                    }
                }
            }
        }
    }

    if(!this->getListRegle().isEmpty()){//affichage composants issus des régles + calcul prix total
        resumeNom +="\nRégles de Nomenclature\n\n";
        for (int i = 0; i< this->getListRegle().size();i++){
            RegleCode r = this->getListRegle().value(i);

            if(r.getActif()){//si la régle est valable ( la condition entre les codes est vérifiée)
                for(int k =0;k <r.getListOperation().size();k++){
                    Operation op = r.getListOperation().value(k);

                    this->nbHCdp += op.getNbHCdp();//mise à jour de la somme des opérations de cdp
                    this->nbHTech += op.getNbHTech();//mise à jour de la somme des opérations de tech
                    this->nbHOuv += op.getNbHOuv();//mise à jour de la somme des opérations d' ouvrier

                    double prixOp = op.getCoutHoraireTot()*(op.getQte().toDouble());
                    QString operand = (op.getAction() == "add") ? "+" : "-";
                    resumeNom += operand+" "+op.getQte()+" "+op.getName()+
                            " : "+operand+QString::number(prixOp)+"€\n";
                    if(operand == "+")
                        prixTotMdo += prixOp;
                    else
                        prixTotMdo -=prixOp;
                }
            }

        }

    }
    return resumeNom;
}


QString Produit::resumeCodeProduit(){
    QString resumeConf="";
    if(!this->getListeSection().isEmpty()){
        for (int p = 0; p < this->getListeSection().size(); p++){
            Section section = this->getListeSection().value(p);
            resumeConf += "\n"+section.getNameS()+"\n";
            if(!section.getListeDeroul().isEmpty()){
                for (int k = 0; k < section.getListeDeroul().size(); k++){
                    if(!section.getListeDeroul().value(k).getListCode().isEmpty()){
                        for (int i = 0; i < section.getListeDeroul().value(k).getListCode().size(); i++){
                            resumeConf += "champ: "+section.getListeDeroul().value(k).getListCode().value(i).getChamp()+"\n codeName: "+
                                    section.getListeDeroul().value(k).getListCode().value(i).getCodeName()+ "\n codeValue: "+
                                    section.getListeDeroul().value(k).getListCode().value(i).getCodeVal() + "\n codePos: "+
                                    QString::number(section.getListeDeroul().value(k).getListCode().value(i).getPos())+"\n";
                        }
                    }
                }
            }

            if(!section.getOptCocher().isEmpty()){
                for (int k = 0; k < section.getOptCocher().size(); k++){

                    resumeConf += "champ: "+section.getOptCocher().value(k).getCode().getChamp()+"\n codeName: "+
                            section.getOptCocher().value(k).getCode().getCodeName()+ "\n codeValue: "+
                            section.getOptCocher().value(k).getCode().getCodeVal() + "\n codePos: "+
                            QString::number(section.getOptCocher().value(k).getCode().getPos())+"\n";
                }
            }
        }
        return resumeConf;

    }
    else{

        return "ERR";
    }
}

QString Produit::afficheCode(){
    QString code = "";
    code += this->getTag()+"_";
    if(!this->getListeSection().isEmpty()){
        for (int p = 0; p < this->getListeSection().size(); p++){
            Section s = this->getListeSection().value(p);
            for (int k = 0; k < s.getListInfoChamp().size(); k++){
                InfoChamp i = s.getListInfoChamp().value(k);
                if(i.getValChamp() == "non")
                    codeProduit.replace( i.getCode().getPos(),"0");
                else{

                    if(!(i.getCode().getCodeVal().contains(QRegExp("^[A-Za-z]+$")))){    // Si le code value est un entier, et pas un char, on doit le convertir en base 36 (0..9,A...Z)
                        int valueEntier = (i.getCode().getCodeVal()).toInt();
                        QString valueHexa = (QString::number( valueEntier, 36 )).toUpper();//base 36, avec les lettres en majuscules.
                        codeProduit.replace(i.getCode().getPos(), valueHexa);
                    }
                    else
                        codeProduit.replace(i.getCode().getPos(), i.getCode().getCodeVal());//si le code value est un char ( a...z ou A...Z) on l'ajoute au code produit direct.

                }
            }
        }
    }
    return code + readCode();
}

QString Produit::readCode(){
    QString code="";
    for (int i=0 ; i <codeProduit.size() ; i++){

        code += codeProduit.value(i);

    }
    return code;
}


Code Produit::findCodeProduit(QString name){
    if(!this->getListeSection().isEmpty()){
        for (int p = 0; p < this->getListeSection().size(); p++){
            Section section = this->getListeSection().value(p);
            if(!section.getListeDeroul().isEmpty()){
                for (int k = 0; k < section.getListeDeroul().size(); k++){
                    if(!section.getListeDeroul().value(k).getListCode().isEmpty()){
                        for (int i = 0; i < section.getListeDeroul().value(k).getListCode().size(); i++){
                            Code c = section.getListeDeroul().value(k).getListCode().value(i);
                            if(c.getCodeName() == name){
                                return c;
                            }
                        }
                    }
                }
            }

            if(!section.getOptCocher().isEmpty()){
                for (int k = 0; k < section.getOptCocher().size(); k++){
                    Code c = section.getOptCocher().value(k).getCode();
                    if(c.getCodeName() == name){
                        return c;
                    }
                }
            }
        }
    }
    Code c;
    c.setCodeName("ERR");
    return c;
}



Code Produit::findCodeInfoChamp(QString name){//retourne le code prduit
    if(!this->getListeSection().isEmpty()){
        for (int p = 0; p < this->getListeSection().size(); p++){
            Section section = this->getListeSection().value(p);
            if(!section.getListInfoChamp().isEmpty()){
                for (int k = 0; k < section.getListInfoChamp().size(); k++){
                    InfoChamp info = section.getListInfoChamp().value(k);
                    Code c = info.getCode();
                    if(c.getCodeName() == name){
                        return c;
                    }
                }
            }
        }
    }

    Code c;
    c.setCodeName("ERR");
    return c;
}
void Produit::replaceRegle(RegleCode r){
    for(int i=0 ; i< this->getListRegle().size() ; i++){
        if(this->getListRegle().value(i).getName() == r.getName()){
            QList<RegleCode> rList = this->getListRegle();
            rList.replace(i,r);
            this->setListRegle(rList);
        }
    }
}
void Produit::replaceCode(QString name,Code c){
    if(!this->getListeSection().isEmpty()){
        for (int p = 0; p < this->getListeSection().size(); p++){//Section1/section2...
            Section section = this->getListeSection().value(p);
            if(!section.getListeDeroul().isEmpty()){
                for (int k = 0; k < section.getListeDeroul().size(); k++){//listederoul1/listeDeroul2...
                    if(!section.getListeDeroul().value(k).getListCode().isEmpty()){
                        for (int i = 0; i < section.getListeDeroul().value(k).getListCode().size(); i++){//code1/code2...
                            if(section.getListeDeroul().value(k).getListCode().value(i).getCodeName() == c.getCodeName()){
                                if(section.getListeDeroul().value(k).getGenerique() == true){//si notre liste déroul est automatisée
                                    //il faut qu'on remplisse la nomenclature de tt les champs
                                    c.setChamp(section.getListeDeroul().value(k).getListCode().value(i).getChamp());
                                }
                                QList<Code> cList = section.getListeDeroul().value(k).getListCode();
                                cList.replace(i,c);
                                ListDeroul lD = section.getListeDeroul().value(k);
                                lD.setListCode(cList);
                                QList<ListDeroul> lDeroul = section.getListeDeroul();
                                lDeroul.replace(k,lD);
                                section.setListesListDeroul(lDeroul);
                                QList<Section> lSection = this->getListeSection();
                                lSection.replace(p,section);
                                this->setListSection(lSection);
                            }
                        }
                    }
                }
            }
            if(!section.getOptCocher().isEmpty()){
                for (int k = 0; k < section.getOptCocher().size(); k++){
                    if(section.getOptCocher().value(k).getCode().getCodeName() == name){

                        OptCocher o = section.getOptCocher().value(k);
                        o.setCode(c);

                        QList<OptCocher> lOptCoch = section.getOptCocher();
                        lOptCoch.replace(k,o);

                        section.setListesOptCocher(lOptCoch);
                        QList<Section> lSection = this->getListeSection();
                        lSection.replace(p,section);
                        this->setListSection(lSection);
                    }
                }
            }
        }
    }
}



Composant Produit::findComposant(QString id){
    if(!this->getListeComposant().isEmpty())
        for (int i = 0; i <this->getListeComposant().size() ; i++){
            Composant c = this->getListeComposant().value(i);
            if(c.getId() == id){
                return c;
            }
        }
    Composant c;
    c.setName("ERR");
    return c;
}



RegleCode Produit::findRegle(QString name){
    if(!this->getListRegle().isEmpty())
        for (int i = 0; i <this->getListRegle().size() ; i++){
            RegleCode r = this->getListRegle().value(i);
            if(r.getName() == name){
                return r;
            }
        }
    RegleCode r;
    r.setName("ERR");
    return r;
}


Operation Produit::findOperation(QString id){
    if(!this->getListeComposant().isEmpty())
        for (int i = 0; i <this->getListOperation().size() ; i++){
            Operation op = this->getListOperation().value(i);
            if(op.getId() == id){
                return op;
            }
        }
    Operation op;
    op.setName("ERR");
    return op;
}


bool Produit::afficheMessage(QString &message){

    if(!this->getListRegle().isEmpty()){
        for (int i = 0; i< this->getListRegle().size();i++){
            RegleCode r = this->getListRegle().value(i);
            if (r.getActif() && r.getMessage()!= ""){
                message = r.getMessage();
                return true;
            }
        }
    }
    return false;
}

Produit::~Produit()
{
}

