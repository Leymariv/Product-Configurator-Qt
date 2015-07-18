/*
 *Auteur: Valmon Leymarie
 *
 *
 *
 *Classe des données de l'applications. Ces données seront lues à partir des fichiers xml
 * présents dans les répertoires correspondants.
 *
 *
 */

#include "data.h"



Data::Data()
{

    initializePaths();

    retrieveFolder();

    readXml("Conf.xml");
    readXml("IndexProduits.xml");

}

void Data :: readXml(QString file){


    QDomDocument *dom = new QDomDocument("DomDoc"); // Création de l'objet DOM
    QFile xml_doc(QApplication::applicationDirPath()+this->pathXML+file);
    if(!xml_doc.open(QIODevice::ReadOnly)){// Si on n'arrive pas à ouvrir le fichier XML.
        QMessageBox::critical(this,"Erreur à l'ouverture des documents XML","Vérifiez le nom et le chemin du document");
        return;
    }
    if (!dom->setContent(&xml_doc)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
    {
        xml_doc.close();
        QMessageBox::critical(this,"Erreur à l'ouverture des documents XML","Impossible d'attribuer le document:\n"+
                              xml_doc.fileName()+".\nVérifiez la syntaxe du document en le lançant dans firefox.");
        qFatal("erreur");
        return;
    }

    QDomElement dom_element = dom->documentElement();

    //Récupérer la version du xml
    QFile fileTemp(QApplication::applicationDirPath()+this->pathXML+file);
    if(!fileTemp.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", fileTemp.errorString());
    }
    QTextStream in(&fileTemp);
    if(file=="IndexProduits.xml"){
        //appeler la focntion de lecture du xml
        buildIndexProduit(dom_element,file);
    }
    else if(file.contains("Produit.xml")){
        buildDataProduit(dom_element,file);
    }
    else if(file.contains("Marche.xml")){
        buildDataMarche(dom_element,file);
    }
    else if (file.contains("Nomenclature.xml")){
        buildDataNomenclature(dom_element,file);
    }
    else if (file == "Conf.xml"){
        buildData(dom_element,file);
    }
    else if (file.contains("Operation.xml")){
        buildDataOP(dom_element,file);
    }

    xml_doc.close();
}

void Data::buildIndexProduit(QDomElement dom_element, QString file){
    QDomNode noeud = dom_element.firstChild();
    while(!noeud.isNull())// Noeud1 du produit
    {
        QDomElement element = noeud.toElement();
        if(!element.isNull())
        {
            QString dossier="";
            dossier = VerifieXmlRead("dossier",element,file); //dossier du produit
            QFile file(QApplication::applicationDirPath()+this->pathXML+dossier+"/Produit.xml");
            if (!file.exists()){
                QMessageBox::critical(this,"Fichier Introuvalble","Fichier "+
                                      file.fileName()+" introuvlable");
                qFatal("Fichier introuvlable");
            }
            readXml(dossier+"/Produit.xml");
            readXml(dossier+"/Nomenclature.xml");
            readXml(dossier+"/Operation.xml");
            readXml(dossier+"/Marche.xml");
        }
        noeud = noeud.nextSibling();
    }

}
void Data::buildDataProduit(QDomElement dom_element, QString file){
    QDomNode noeud = dom_element.firstChild();
    while(!noeud.isNull())// Noeud1 du produit
    {
        QDomElement element = noeud.toElement();
        if(!element.isNull())
        {
            Produit p;

            estPresent(VerifieXmlRead("name",element,file));

            int nbCode = 0;

            p.setVersionProduitXML(VerifieXmlRead("versionXML",dom_element,file));
            p.setName(VerifieXmlRead("name",element,file)); //nom du produit
            p.setLienPdf(QApplication::applicationDirPath()+this->pathFiche+
                         VerifieXmlRead("lienPdf",element,file));

            p.setLienImg(QApplication::applicationDirPath()+this->pathFiche+
                         VerifieXmlRead("lienImg",element,file));
            p.setTag(VerifieXmlRead("tag",element,file));


            QDomNode noeud2 = element.firstChild();


            while(!noeud2.isNull())// Noeud2 Description
            {
                QDomElement element2 = noeud2.toElement();

                if(element2.tagName() == "Description"){
                    p.setText(VerifieXmlRead("texte",element2,file));

                }

                else if(element2.tagName() == "IHM"){//Noeud2 IHM
                    p.setNbSection((VerifieXmlRead("nb",element2,file)).toInt());

                    QDomNode noeud3 = element2.firstChild();

                    while(!noeud3.isNull())// Noeud3 Section
                    {
                        QDomElement element3 = noeud3.toElement();

                        Section s;

                        s.setNameS(VerifieXmlRead("name",element3,file));


                        QDomNode noeud4 = element3.firstChild();
                        while(!noeud4.isNull()){// Noeud4 Liste déroulante/OPTCocher/SaisieLibre
                            QDomElement element4 = noeud4.toElement();

                            if(element4.tagName() == "ListeDeroulante"){
                                ListDeroul l;
                                l.setNameL( VerifieXmlRead("name",element4,file));

                                if(element4.attribute("code",0) == 0){//si le code produit est rempli
                                    //indépendament des actions de l'utilisateur
                                    l.setGenerique(false);

                                    QDomNode noeud5 = element4.firstChild();
                                    while(!noeud5.isNull()){// Noeud5 Champs de la liste déroulante
                                        QDomElement element5 = noeud5.toElement();

                                        Code c;
                                        c.setChamp(VerifieXmlRead("champValue",element5,file));
                                        c.setCodeName(VerifieXmlRead("code",element5,file));
                                        c.setPos(VerifieXmlRead("position",element5,file).toInt());

                                        nbCode = c.getPos();

                                        c.setCodeVal(VerifieXmlRead("codeValue",element5,file));

                                        QList<Code> lCode = l.getListCode();
                                        lCode.append(c);
                                        l.setListCode(lCode);

                                        noeud5 = noeud5.nextSibling();
                                    }
                                }

                                else{//si le code produit est rempli
                                    //en fonction de la valeur choisie par l'utilisateur

                                    l.setGenerique(true);//cette liste est une liste "automatisée" -> Generique

                                    Code c;

                                    c.setCodeName(VerifieXmlRead("code",element4,file));
                                    c.setPos(VerifieXmlRead("position",element4,file).toInt());

                                    nbCode = c.getPos();

                                    QDomNode noeud5 = element4.firstChild();
                                    while(!noeud5.isNull()){// Noeud5 Champs de la liste déroulante
                                        QDomElement element5 = noeud5.toElement();

                                        c.setChamp(VerifieXmlRead("champValue",element5,file));

                                        if(c.getCodeName()=="codeITINBVOIES"){
                                        }


                                        c.setCodeVal("x");

                                        QList<Code> lCode = l.getListCode();
                                        lCode.append(c);
                                        l.setListCode(lCode);

                                        noeud5 = noeud5.nextSibling();
                                    }
                                }


                                QList<ListDeroul> listDeroulantes = s.getListeDeroul();
                                listDeroulantes.append(l);
                                s.setListesListDeroul(listDeroulantes);


                            }

                            else if(element4.tagName() == "OptionCocher"){

                                OptCocher o;
                                Code c;
                                c.setChamp(VerifieXmlRead("name",element4,file));

                                if(element4.attribute("code",0) != 0){
                                    c.setCodeName(VerifieXmlRead("code",element4,file));
                                    c.setPos(VerifieXmlRead("position",element4,file).toInt());
                                    c.setCodeVal(VerifieXmlRead("codeValue",element4,file));

                                    nbCode = c.getPos();
                                }

                                o.setCode(c);

                                QList<OptCocher> listOptions = s.getOptCocher();
                                listOptions.append(o);
                                s.setListesOptCocher(listOptions);

                            }

                            else{
                                QMessageBox::critical(this,"Erreur "+file,
                                                      "Erreur de format "+element4.tagName()+
                                                      " ligne "+ QString::number(element4.lineNumber()));
                                return;
                            }
                            noeud4 = noeud4.nextSibling();
                        }

                        QList<Section> listeSection = p.getListeSection();
                        listeSection.append(s);
                        p.setListSection(listeSection);
                        noeud3 = noeud3.nextSibling();
                    }
                }

                else if (noeud2.nodeName() == "Codes"){//Noeud2 Codes
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 Codes (code1/code2...)
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {
                                RegleCode regle;

                                regle.setName(VerifieXmlRead("name",element3,file));
                                regle.setCode1(VerifieXmlRead("code1",element3,file));
                                regle.setOperation(VerifieXmlOperation("operation",element3,file));
                                regle.setCode2(VerifieXmlRead("code2",element3,file));
                                regle.setRegleType("OPERATION");

                                //                                Code code = p.findCodeProduit(VerifieXmlRead("name",element3,file));
                                //                                if (code.getCodeName()=="ERR"){
                                //                                    QMessageBox::critical(this,"Erreur "+file,"Code introuvable dans la liste des codes:\n"+
                                //                                                          element3.tagName()+" ligne "+ QString::number(element3.lineNumber()));
                                //                                }
                                QList<RegleCode> rList = p.getListRegle();
                                rList.append(regle);
                                p.setListRegle(rList);
                            }
                            noeud3 = noeud3.nextSibling();
                        }
                    }
                }

                else if (noeud2.nodeName() == "Regles"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 Regles
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {
                                RegleCode regle;
                                regle.setName(VerifieXmlRead("name",element3,file));
                                //vérifier si on est dans le cas d'une régle a comparaison ou d'une régle a operande
                                if (element3.attribute("code1",0) == 0 ){//on est dans le cas d'une régle à comparaison. Elle peut être de type:
                                    //- comparaison nombre (comparaison entre la valeur d"'un code et d'un entier)
                                    //- comparasion code (comparaison entre les valeurs de deux codes)
                                    regle.setCode1(VerifieXmlRead("codeValue1",element3,file));
                                    regle.setComparaison(VerifieXmlComparaison("comparaison",element3,file));
                                    if (element3.attribute("nombre",0) == 0){//cas d'une régle a comparaison de code
                                        regle.setCode2(VerifieXmlRead("codeValue2",element3,file));
                                        regle.setRegleType("COMPCODE");
                                    }
                                    else{//cas d'une régle a comparaison de nombre
                                        regle.setNombre(VerifieXmlRead("nombre",element3,file));
                                        regle.setRegleType("COMPNBR");
                                    }
                                }
                                else{//c'est une rélge à operande
                                    regle.setCode1(VerifieXmlRead("code1",element3,file));
                                    regle.setOperande(VerifieXmlOperande("operande",element3,file));
                                    regle.setCode2(VerifieXmlRead("code2",element3,file));
                                    regle.setRegleType("OPERANDE");
                                }

                                QDomNode noeud4 = element3.firstChild();
                                while(!noeud4.isNull())// Noeud4 Messages
                                {
                                    QDomElement element4 = noeud4.toElement();
                                    if(!element4.isNull())
                                    {
                                        regle.setMessage(VerifieXmlRead("text",element4,file));
                                    }
                                    noeud4 = noeud4.nextSibling();
                                }
                                QList<RegleCode> rList = p.getListRegle();
                                rList.append(regle);
                                p.setListRegle(rList);
                            }
                            noeud3 = noeud3.nextSibling();
                        }
                    }
                }

                else{
                    QMessageBox::critical(this,"Erreur "+file,
                                          "Erreur de format "+element2.tagName()+
                                          " ligne "+ QString::number(element2.lineNumber()));
                    return;
                }

                noeud2 = noeud2.nextSibling();
            }

            //Initialisation du code produit a 0000000000000
            for(int i=0; i<= nbCode ; i++){
                QList<QString> c = p.getCodeProduit();
                c.append("0");
                p.setCodeProduit(c);
            }

            listP.append(p);
        }
        noeud = noeud.nextSibling();
    }

}

void Data::buildDataNomenclature(QDomElement dom_element, QString file){


    QDomNode noeud = dom_element.firstChild();
    while(!noeud.isNull())// Noeud1 name produit
    {

        QDomElement element = noeud.toElement();
        if(!element.isNull())
        {
            Produit p = this->findProduit(VerifieXmlRead("nameProduit",element,file));

            p.setVersionNomenclatureXML(VerifieXmlRead("versionXML",dom_element,file));
            QDomNode noeud2 = element.firstChild();
            while(!noeud2.isNull())// Noeud2 Composants configuration/BAse commune/CodeProduit/RegesCodes
            {
                if (noeud2.nodeName() == "ComposantsConfiguration"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 RefFGS/ AchatAffaire
                        {
                            QDomElement element3 = noeud3.toElement();

                            if(noeud3.nodeName() == "RefFGS"){
                                if(!element3.isNull())
                                {
                                    QDomNode noeud4 = element3.firstChild();
                                    while(!noeud4.isNull())// Noeud4 : Composant name, ref
                                    {
                                        QDomElement element4 = noeud4.toElement();
                                        if(!element4.isNull())
                                        {
                                            ComposantFG cFG = ComposantFG() ;
                                            cFG.setName(VerifieXmlRead("name",element4,file));
                                            cFG.setPrixU(VerifieXmlDouble("prixU",element4,file));
                                            cFG.setRefFG(VerifieXmlRead("refFG",element4,file));
                                            cFG.setId(VerifieXmlRead("id",element4,file));
                                            cFG.setRef(cFG.getRefFG());
                                            QList<Composant> listComp = p.getListeComposant();
                                            listComp.append(cFG);
                                            p.setListComposant(listComp);
                                        }

                                        noeud4 = noeud4.nextSibling();
                                    }
                                }
                            }
                            else if(noeud3.nodeName() == "AchatAffaire"){
                                if(!element3.isNull())
                                {
                                    QDomNode noeud4 = element3.firstChild();
                                    while(!noeud4.isNull())// Noeud4 : Composant, name, ref...
                                    {
                                        QDomElement element4 = noeud4.toElement();

                                        if(!element4.isNull())
                                        {
                                            ComposantAffaire cA = ComposantAffaire();
                                            cA.setName(VerifieXmlRead("name",element4,file));
                                            cA.setPrixU(VerifieXmlDouble("prixU",element4,file));
                                            cA.setRefFournisseur(VerifieXmlRead("ref",element4,file));
                                            cA.setFournisseur(VerifieXmlRead("fournisseur",element4,file));
                                            cA.setId(VerifieXmlRead("id",element4,file));
                                            cA.setRef(cA.getRefFournisseur());

                                            QList<Composant> listComp = p.getListeComposant();
                                            listComp.append(cA);
                                            p.setListComposant(listComp);

                                        }
                                        noeud4 = noeud4.nextSibling();
                                    }

                                }

                            }
                            else{
                                QMessageBox::critical(this,"Erreur "+file,"Erreur de format "+
                                                      noeud3.nodeName()+" ligne "+ QString::number(noeud3.lineNumber()));
                            }

                            noeud3 = noeud3.nextSibling();
                        }

                    }

                }

                else if (noeud2.nodeName() == "BaseCommune"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 Composants
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {
                                Composant c = p.findComposant(VerifieXmlRead("id",element3,file));
                                if (c.getName()=="ERR"){
                                    QMessageBox::critical(this,"Erreur "+file,"Composant de la base comunne introuvable dans la liste des composants:\n"+
                                                          element3.tagName()+" ligne "+ QString::number(element3.lineNumber()));
                                }

                                c.setQte(VerifieXmlRead("quantité",element3,file));
                                QList<Composant> bC = p.getBaseCommuneComposants();
                                bC.append(c);
                                p.setBaseCommuneComposants(bC);

                            }
                            noeud3 = noeud3.nextSibling();
                        }

                    }
                }

                else if (noeud2.nodeName() == "CodeProduits"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 Codes (code1/code2...)
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {
                                Code code = p.findCodeProduit(VerifieXmlRead("name",element3,file));
                                RegleCode regle;

                                if (code.getCodeName()=="ERR"){

                                    regle = p.findRegle(VerifieXmlRead("name",element3,file));
                                    if (regle.getName()=="ERR"){
                                        QMessageBox::critical(this,"Erreur "+file,"Code introuvable dans la liste des codes:\n"+
                                                              element3.tagName()+" ligne "+ QString::number(element3.lineNumber()));
                                    }
                                }
                                QDomNode noeud4 = element3.firstChild();
                                while(!noeud4.isNull())// Noeud4 Composants (composant1/composant2...)
                                {
                                    QDomElement element4 = noeud4.toElement();
                                    if(!element4.isNull())
                                    {
                                        Composant comp = p.findComposant(VerifieXmlRead("id",element4,file));

                                        if (comp.getName()=="ERR"){
                                            QMessageBox::critical(this,"Erreur "+file,"Composant introuvable dans la liste des composants:\n"+
                                                                  element4.tagName()+" ligne "+ QString::number(element4.lineNumber()));
                                        }

                                        comp.setAction(VerifieXmlRead("action",element4,file));
                                        comp.setQte(VerifieXmlRead("quantité",element4,file));

                                        if (code.getCodeName()=="ERR"){//on a  afaire a une régle pas a un code
                                            QList<Composant> lComp = regle.getListComp();
                                            lComp.append(comp);
                                            regle.setListComp(lComp);
                                            p.replaceRegle(regle);
                                        }
                                        else{
                                            QList<Composant> lComp = code.getListComp();
                                            lComp.append(comp);
                                            code.setListComp(lComp);
                                            p.replaceCode(code.getCodeName(),code);
                                        }
                                    }
                                    noeud4 = noeud4.nextSibling();
                                }
                            }
                            noeud3 = noeud3.nextSibling();
                        }
                    }
                }

                else if (noeud2.nodeName() == "ReglesCode"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 Regles
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {
                                RegleCode regle;

                                regle.setName(VerifieXmlRead("name",element3,file));
                                regle.setCode1(VerifieXmlRead("code1",element3,file));
                                regle.setCode2(VerifieXmlRead("code2",element3,file));
                                regle.setOperande(VerifieXmlOperande("operande",element3,file));
                                regle.setRegleType("OPERANDE");

                                QDomNode noeud4 = element3.firstChild();
                                while(!noeud4.isNull())// Noeud4 Composants
                                {
                                    QDomElement element4 = noeud4.toElement();
                                    if(!element4.isNull())
                                    {
                                        Composant comp = p.findComposant(VerifieXmlRead("id",element4,file));
                                        comp.setAction(VerifieXmlRead("action",element4,file));
                                        comp.setQte(VerifieXmlRead("quantité",element4,file));
                                        QList<Composant> lComp = regle.getListComp();
                                        lComp.append(comp);
                                        regle.setListComp(lComp);
                                    }
                                    noeud4 = noeud4.nextSibling();
                                }
                                QList<RegleCode> rList = p.getListRegle();
                                rList.append(regle);
                                p.setListRegle(rList);
                            }

                            noeud3 = noeud3.nextSibling();
                        }
                    }
                }

                else
                    QMessageBox::critical(this,"Erreur "+file,"Erreur de format "+
                                          noeud2.nodeName()+" ligne "+ QString::number(noeud2.lineNumber()));
                noeud2 = noeud2.nextSibling();
            }

            for(int i=0 ; i< this->listP.size() ; i++){
                if(this->listP.value(i).getName() == p.getName()){
                    this->listP.replace(i,p);
                }
            }

        }
        noeud = noeud.nextSibling();
    }
}


void Data::buildDataMarche(QDomElement dom_element, QString file){
    QDomNode noeud = dom_element.firstChild();
    while(!noeud.isNull())// Noeud1 du produit
    {
        QDomElement element = noeud.toElement();
        if(!element.isNull())
        {
            Produit p = this->findProduit(VerifieXmlRead("nameProduit",element,file));
            p.setVersionMarcheXML(VerifieXmlRead("versionXML",dom_element,file));
            QDomNode noeud2 = element.firstChild();
            while(!noeud2.isNull())// Noeud2 Marché
            {

                QDomElement element2 = noeud2.toElement();
                Marche marche;
                marche.setName(VerifieXmlRead("name",element2,file));

                if(!element2.isNull())
                {
                    QDomNode noeud3 = element2.firstChild();

                    while(!noeud3.isNull())// Noeud3 codets//BASE COMMUNe//Codes//REGLES
                    {
                        QDomElement element3 = noeud3.toElement();

                        if(element3.tagName() == "Codets"){
                            QDomNode noeud4 = element3.firstChild();
                            while(!noeud4.isNull())// Noeud4 codets
                            {
                                QDomElement element4 = noeud4.toElement();
                                Codet codet;
                                codet.setName(VerifieXmlRead("name",element4,file));
                                codet.setPrixVenteU(VerifieXmlDouble("prixVenteU",element4,file));
                                codet.setCodeArticle(VerifieXmlRead("codeArticle",element4,file));
                                codet.setId(VerifieXmlRead("id",element4,file));

                                QList<Codet> codetsL = marche.getCodetsList();
                                codetsL.append(codet);
                                marche.setCodetList(codetsL);

                                noeud4 = noeud4.nextSibling();
                            }
                        }
                        if(element3.tagName() == "BaseCommune"){

                            QDomNode noeud4 = element3.firstChild();
                            while(!noeud4.isNull())// Noeud4 codets
                            {
                                QDomElement element4 = noeud4.toElement();
                                Codet codet = marche.findCodet(VerifieXmlRead("id",element4,file));

                                if (codet.getName()=="ERR"){
                                    QMessageBox::critical(this,"Erreur "+file,"Codet de la base comunne introuvable dans la liste des codets:\n"+
                                                          element4.tagName()+" ligne "+ QString::number(element4.lineNumber()));
                                }

                                codet.setQte(VerifieXmlRead("quantité",element4,file));
                                codet.setAction(VerifieXmlRead("action",element4,file));

                                QList<Codet> codetsL = marche.getBaseCommuneCodets();
                                codetsL.append(codet);
                                marche.setBaseCommuneCodets(codetsL);
                                noeud4 = noeud4.nextSibling();
                            }
                        }
                        if(element3.tagName() == "CodeProduits"){
                            QDomNode noeud4 = element3.firstChild();
                            while(!noeud4.isNull())// Noeud4 codets
                            {
                                QDomElement element4 = noeud4.toElement();
                                Code code = p.findCodeProduit(VerifieXmlRead("name",element4,file));

                                if (code.getCodeName()=="ERR"){
                                    QMessageBox::critical(this,"Erreur "+file,"Code introuvable dans la liste des codes:\n"+
                                                          element4.tagName()+" ligne "+ QString::number(element4.lineNumber()));
                                }

                                QDomNode noeud5 = element4.firstChild();
                                while(!noeud5.isNull())// Noeud4 Codets (codet1/codet2...)
                                {
                                    QDomElement element5 = noeud5.toElement();
                                    Codet codet = marche.findCodet(VerifieXmlRead("id",element5,file));

                                    if (codet.getName()=="ERR"){
                                        QMessageBox::critical(this,"Erreur "+file,"Codet introuvable dans la liste des codets:\n"+
                                                              element5.tagName()+" ligne "+ QString::number(element5.lineNumber()));
                                    }

                                    codet.setQte(VerifieXmlRead("quantité",element5,file));
                                    codet.setAction(VerifieXmlRead("action",element5,file));

                                    QList<Codet> codetsL = code.getListCodet();
                                    codetsL.append(codet);
                                    code.setListCodet(codetsL);

                                    p.replaceCode(code.getCodeName(),code);

                                    noeud5 = noeud5.nextSibling();
                                }
                                noeud4 = noeud4.nextSibling();
                            }
                        }
                        if(element3.tagName() == "ReglesCode"){
                            QDomNode noeud4 = element3.firstChild();
                            while(!noeud4.isNull())// Noeud4 codets
                            {
                                QDomElement element4 = noeud4.toElement();
                                RegleCode regle = p.findRegle(VerifieXmlRead("name",element4,file));

                                if (regle.getName()=="ERR"){
                                    QMessageBox::critical(this,"Erreur "+file,"Code introuvable dans la liste des codes:\n"+
                                                          element4.tagName()+" ligne "+ QString::number(element4.lineNumber()));
                                }

                                QDomNode noeud5 = element4.firstChild();
                                while(!noeud5.isNull())// Noeud4 Codets (codet1/codet2...)
                                {
                                    QDomElement element5 = noeud5.toElement();

                                    Codet codet = marche.findCodet(VerifieXmlRead("id",element5,file));

                                    if (codet.getName()=="ERR"){
                                        QMessageBox::critical(this,"Erreur "+file,"Codet introuvable dans la liste des codets:\n"+
                                                              element5.tagName()+" ligne "+ QString::number(element5.lineNumber()));
                                    }

                                    codet.setQte(VerifieXmlRead("quantité",element5,file));
                                    codet.setAction(VerifieXmlRead("action",element5,file));

                                    QList<Codet> codetsL = regle.getListCodet();
                                    codetsL.append(codet);
                                    regle.setListCodet(codetsL);

                                    noeud5 = noeud5.nextSibling();
                                }

                                for(int i=0 ; i< p.getListRegle().size() ; i++){
                                    if(p.getListRegle().value(i).getName() == regle.getName()){
                                        QList<RegleCode> rList = p.getListRegle();
                                        rList.replace(i,regle);
                                        p.setListRegle(rList);
                                    }
                                }
                                noeud4 = noeud4.nextSibling();
                            }
                        }
                        noeud3 = noeud3.nextSibling();
                    }

                }

                QList<Marche> marchesL = p.getListMarche();
                marchesL.append(marche);
                p.setListMarche(marchesL);

                noeud2 = noeud2.nextSibling();
            }
            for(int i=0 ; i< this->listP.size() ; i++){
                if(this->listP.value(i).getName() == p.getName()){
                    this->listP.replace(i,p);
                }
            }
        }
        noeud = noeud.nextSibling();
    }
}

void Data::buildData(QDomElement dom_element, QString file){

    versionConfXML = VerifieXmlRead("versionXML",dom_element,file);
    QDomNode noeud = dom_element.firstChild();
    if(!noeud.isNull())// Noeud1 Mdo
    {
        QDomElement element = noeud.toElement();
        if(!element.isNull())
        {
            QDomNode noeud2 = element.firstChild();
            while(!noeud2.isNull())// Noeud2 Mdo champs
            {
                QDomElement element2 = noeud2.toElement();
                this->listMdo.append(Mdo(VerifieXmlRead("name",element2,file),
                                         VerifieXmlDouble("coutH",element2,file)));
                noeud2 = noeud2.nextSibling();
            }

        }
    }
    noeud = noeud.nextSibling();
    if(!noeud.isNull())// Noeud1 Frais
    {
        QDomElement element = noeud.toElement();
        if(!element.isNull())
        {


            QDomNode noeud2 = element.firstChild();
            while(!noeud2.isNull())// Noeud2 Frais champs
            {

                QDomElement element2 = noeud2.toElement();
                this->listFrais.append(Frais(VerifieXmlRead("name",element2,file),
                                             VerifieXmlDouble("pourcentage",element2,file)));
                noeud2 = noeud2.nextSibling();
            }

        }
    }
}


void Data::buildDataOP(QDomElement dom_element, QString file){
    QDomNode noeud = dom_element.firstChild();

    while(!noeud.isNull())// Noeud1 name produit
    {
        QDomElement element = noeud.toElement();
        if(!element.isNull())
        {
            Produit p = this->findProduit(VerifieXmlRead("nameProduit",element,file));
            p.setVersionOperationXML(VerifieXmlRead("versionXML",dom_element,file));
            QDomNode noeud2 = element.firstChild();
            while(!noeud2.isNull())// Noeud2 Opérations/BaseComune/codeProduit
            {
                if (noeud2.nodeName() == "OperationsConfiguration"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();
                        while(!noeud3.isNull())// Noeud3 : Opération name, ref
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {

                                Operation op;
                                op.setName(VerifieXmlRead("name",element3,file));
                                op.setId(VerifieXmlRead("id",element3,file));

                                QDomNode noeud4 = element3.firstChild();
                                while(!noeud4.isNull())// Noeud4 : Mdo
                                {
                                    QDomElement element4 = noeud4.toElement();
                                    if(!element4.isNull())
                                    {
                                        op.setNbHCdp(VerifieXmlDouble("tpsCdp",element4,file));
                                        op.setNbHTech(VerifieXmlDouble("tpsTech",element4,file));
                                        op.setNbHOuv(VerifieXmlDouble("tpsOuv",element4,file));

                                        //cout horaire total de l'opération
                                        op.setCoutHoraireTot(op.getNbHCdp()*this->listMdo.value(0).getCoutH()+//cout total cdp
                                                             op.getNbHTech()*this->listMdo.value(1).getCoutH()+//cout total tech
                                                             op.getNbHOuv()*this->listMdo.value(2).getCoutH());//cout total ouvrier

                                        QList<Operation> listOp = p.getListOperation();
                                        listOp.append(op);
                                        p.setListOperation(listOp);
                                    }
                                    noeud4 = noeud4.nextSibling();
                                }
                            }

                            noeud3 = noeud3.nextSibling();
                        }


                    }

                }

                else if (noeud2.nodeName() == "BaseCommune"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 Op
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {
                                Operation op = p.findOperation(VerifieXmlRead("id",element3,file));
                                if (op.getName()=="ERR"){
                                    QMessageBox::critical(this,"Erreur "+file,"Composant de la base comunne introuvable dans la liste des composants:\n"+
                                                          element3.tagName()+" ligne "+ QString::number(element3.lineNumber()));
                                }

                                op.setQte(VerifieXmlRead("quantité",element3,file));
                                QList<Operation> bOp = p.getBaseCommuneOperations();
                                bOp.append(op);
                                p.setBaseCommuneOperations(bOp);
                            }
                            noeud3 = noeud3.nextSibling();
                        }

                    }

                }

                else if (noeud2.nodeName() == "CodeProduits"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 Codes
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {
                                Code code = p.findCodeProduit(VerifieXmlRead("name",element3,file));

                                if (code.getCodeName()=="ERR"){
                                    QMessageBox::critical(this,"Erreur "+file,"Code introuvable dans la liste des codes:\n"+
                                                          element3.tagName()+" ligne "+ QString::number(element3.lineNumber()));
                                }

                                QDomNode noeud4 = element3.firstChild();
                                while(!noeud4.isNull())// Noeud4 Operations
                                {
                                    QDomElement element4 = noeud4.toElement();
                                    if(!element4.isNull())
                                    {
                                        Operation op = p.findOperation(VerifieXmlRead("id",element4,file));

                                        if (op.getName()=="ERR"){
                                            QMessageBox::critical(this,"Erreur "+file,"Composant introuvable dans la liste des composants:\n"+
                                                                  element4.tagName()+" ligne "+ QString::number(element4.lineNumber()));
                                        }

                                        op.setAction(VerifieXmlRead("action",element4,file));
                                        op.setQte(VerifieXmlRead("quantité",element4,file));
                                        QList<Operation> lOp = code.getListOp();
                                        lOp.append(op);
                                        code.setListOp(lOp);

                                        p.replaceCode(code.getCodeName(),code);
                                    }
                                    noeud4 = noeud4.nextSibling();
                                }
                            }
                            noeud3 = noeud3.nextSibling();
                        }
                    }
                }

                else if (noeud2.nodeName() == "ReglesCode"){
                    QDomElement element2 = noeud2.toElement();
                    if(!element2.isNull())
                    {
                        QDomNode noeud3 = element2.firstChild();

                        while(!noeud3.isNull())// Noeud3 Regles
                        {
                            QDomElement element3 = noeud3.toElement();
                            if(!element3.isNull())
                            {
                                RegleCode regle = p.findRegle(VerifieXmlRead("name",element3,file));
                                if (regle.getName()=="ERR"){
                                    QMessageBox::critical(this,"Erreur "+file,"Code introuvable dans la liste des codes:\n"+
                                                          element3.tagName()+" ligne "+ QString::number(element3.lineNumber()));
                                }

                                QDomNode noeud4 = element3.firstChild();
                                while(!noeud4.isNull())// Noeud4 Operations
                                {
                                    QDomElement element4 = noeud4.toElement();
                                    if(!element4.isNull())
                                    {
                                        Operation op = p.findOperation(VerifieXmlRead("id",element4,file));
                                        op.setAction(VerifieXmlRead("action",element4,file));
                                        op.setQte(VerifieXmlRead("quantité",element4,file));

                                        QList<Operation> lOp = regle.getListOperation();
                                        lOp.append(op);
                                        regle.setListOperation(lOp);
                                    }
                                    noeud4 = noeud4.nextSibling();
                                }
                                for(int i=0 ; i< p.getListRegle().size() ; i++){
                                    if(p.getListRegle().value(i).getName() == regle.getName()){
                                        QList<RegleCode> rList = p.getListRegle();
                                        rList.replace(i,regle);
                                        p.setListRegle(rList);
                                    }
                                }
                            }

                            noeud3 = noeud3.nextSibling();
                        }
                    }
                }

                else
                    QMessageBox::critical(this,"Erreur "+file,"Erreur de format "+
                                          noeud2.nodeName()+" ligne "+ QString::number(noeud2.lineNumber()));
                noeud2 = noeud2.nextSibling();
            }

            for(int i=0 ; i< this->listP.size() ; i++){
                if(this->listP.value(i).getName() == p.getName()){
                    this->listP.replace(i,p);
                }
            }

        }
        noeud = noeud.nextSibling();
    }
}

QString Data :: VerifieXmlRead(QString champ, QDomElement element, QString file){
    if (element.attribute(champ,0) == 0){
        QMessageBox::critical(this,"Erreur "+file,
                              "Erreur de format "+element.tagName()+" ligne "+ QString::number(element.lineNumber()));
        qFatal("Erreur de format");
        return 0;
    }
    return element.attribute(champ);
}

QString Data :: VerifieXmlOperation(QString champ, QDomElement element, QString file){
    if (element.attribute(champ,0) =="+" ||element.attribute(champ,0) == "-" ||
            element.attribute(champ,0) == "*" ||element.attribute(champ,0) =="/"){

        return element.attribute(champ);
    }
    else{
        QMessageBox::critical(this,"Erreur "+file,
                              "Erreur de format "+element.tagName()+" ligne "+ QString::number(element.lineNumber()));
        qFatal("Erreur de format");
        return 0;
    }
}

QString Data :: VerifieXmlComparaison(QString champ, QDomElement element, QString file){
    if (element.attribute(champ,0) == "EGAL" ||element.attribute(champ,0) == "SUP" ||
            element.attribute(champ,0) == "INF"){
        return element.attribute(champ);
    }
    else{
        QMessageBox::critical(this,"Erreur "+file,
                              "Erreur de format "+element.tagName()+" ligne "+ QString::number(element.lineNumber()));
        qFatal("Erreur de format");
        return 0;
    }
}

QString Data :: VerifieXmlOperande(QString champ, QDomElement element, QString file){
    if (element.attribute(champ,0) == "AND" ||element.attribute(champ,0) == "OR" ||
           element.attribute(champ,0) == "NOT AND"||element.attribute(champ,0) == "AND NOT"||
            element.attribute(champ,0) == "NOT AND NOT" || element.attribute(champ,0) == "NOT OR" ||
            element.attribute(champ,0) == "OR NOT" ||element.attribute(champ,0) == "NOT OR NOT"){

        return element.attribute(champ);
    }
    else{

        QMessageBox::critical(this,"Erreur "+file,
                              "Erreur de format "+element.tagName()+" ligne "+ QString::number(element.lineNumber()));
        qFatal("Erreur de format");
        return 0;
    }
}

double Data :: VerifieXmlDouble(QString champ, QDomElement element, QString file){
    if (element.attribute(champ,0) == 0){
        QMessageBox::critical(this,"Erreur "+file,
                              "Erreur de format "+element.tagName()+" ligne "+ QString::number(element.lineNumber()));
        qFatal("Erreur de format");
        return 0;
    }
    QString s = element.attribute(champ);
    if(s.indexOf(",") != -1){
        s.replace(",",".");
    }
    return s.toDouble();
}

QList<Produit> Data::getListeProduit(){
    return this->listP;
}

Produit Data::findProduit(QString name){
    Produit p;
    if(!this->listP.isEmpty())
        for (int i = 0; i <this->listP.size() ; i++){
            p = this->listP.value(i);
            if(p.getName() == name){
                return p;
            }
        }
    else{
        QMessageBox::critical(this,"Erreur interne ",
                              "data.cpp : La liste des Produits est vide" );
        return p;
    }
    QMessageBox::critical(this,"Erreur interne",
                          "Produit "+name+" introuvalbe" );
    return p;
}


bool Data::estPresent(QString name){
    Produit p;
    if(!this->listP.isEmpty())
        for (int i = 0; i <this->listP.size() ; i++){
            p = this->listP.value(i);
            if(p.getName() == name){
                QMessageBox::critical(this,"Erreur "+name+".xml",
                                      "Produit "+name+" déja déclaré" );
                return true;
            }
        }
    return false;
}

void Data::initializePaths(){


    // Ouverture du fichier path.ini
    QString pathIni= QApplication::applicationDirPath()+PATHMAINDOSSIER+"path.ini";

    // Ouverture du fichier INI
    if(!QFile::exists(pathIni)){
        QMessageBox::critical(this,"Fichier Manquant","Erreur path.ini introuvable.");
        qFatal("path.ini introuvable");
    }

    QSettings settings(pathIni, QSettings::IniFormat);

    QString s = INIFILECONTAINER;

    pathXML = settings.value(s+"/PATHXML","ERREUR").toString();

    pathFiche = settings.value(s+"/PATHFICHE","ERREUR").toString();

    pathSyst = settings.value(s+"/PATHSYST","ERREUR").toString();

    pathBA = settings.value(s+"/PATHBA","ERREUR").toString();

    pathIni = settings.value(s+"/PATHINI","ERREUR").toString();

    pathSynchro = settings.value("PathSynchro/PATHSYNCRHRO","ERREUR").toString();

}

void Data::retrieveFolder(){


    //Création des commandes, il faut mettre les paths entre guillemets (pour les espaces)

    QString cmdBA = "xcopy \""+pathSynchro+"\\BA\" \""+QApplication::applicationDirPath()+pathBA;
    QString cmdXML = "xcopy \""+pathSynchro+"\\XML\" \""+QApplication::applicationDirPath()+pathXML;
    QString cmdSYST = "xcopy \""+pathSynchro+"\\SYSTEM\" \""+QApplication::applicationDirPath()+pathSyst;
    QString cmdFiche = "xcopy \""+pathSynchro+"\\FichesProduit\" \""+QApplication::applicationDirPath()+pathFiche;

    //options pour les commandes
    QString opt ="\" /D /E /C /R /H /K /Y /I";



    //il faut rzemplacer les / par des \\ pour que les chemins soient valides
    cmdBA.replace("/","\\");
    cmdXML.replace("/","\\");
    cmdSYST.replace("/","\\");
    cmdFiche.replace("/","\\");

    //création du .bat
    QString fileName = QApplication::applicationDirPath()+PATHMAINDOSSIER+"retrieve.bat";

    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        //écriture dans le .bat

        stream << cmdBA<<opt<<"\n"<<
                  cmdXML<<opt<<"\n"<<
                  cmdSYST<<opt<<"\n"<<
                  cmdFiche<<opt<<"\n"<<
                  endl;

    }
    if(!file.exists()){
        QMessageBox::critical(this,"Fichier Manquant","Erreur retrieve.bat non généré.");
        qFatal("retrieve.bat introuvable");
    }
    else{
        //execution du .bat
        cmdDos("call \""+fileName+"\"");
    }

    QFile ba(pathSynchro+"/BA/BA.xlsx");


    if(!ba.exists()){
        QMessageBox::warning(this,"Erreur de connexion","Erreur de connexion au réseau, disque L:/ inaccessible");
    }
}

void Data::cmdDos(QString commande){
    system(qPrintable(commande));
}

Data::~Data()
{
}



