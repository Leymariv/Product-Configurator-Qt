/*
 *Auteur: Valmon Leymarie
 *
 *
 *
 *Cette classe permet de gérer notre application d'un point de vue général.
 *Elle est constitué d'une interface graphique, notament d'un QStackedWidget
 *qui permet de naviguer d'un menu à l'autre.
 * La liste listMenu, est une simple liste de QString mais l'emplacement dans
 * la liste d'un menu correspond aussi à l'emplacement dans le QStackedWidget.
 * Cela permet en conaissant le nom du menu voulu de changer l'index courant
 * du QStackedWidget pour afficher le menu.
 *
 */

#include "windows.h"

Windows::Windows(QWidget *parent, int iC, int iP) :
    QDialog(parent),
    ui(new Ui::Windows),
    PageInterface(parent, iC,iP)


{
    this->setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
    dataBase = new Data();
    ui->setupUi(this);
    listMenu << "Windows"<<"SaisiCode";
    signalAndSlot();
}






void Windows::signalAndSlot()
{
    QObject::connect(ui->codeBouton, SIGNAL(clicked()), this, SLOT(openLogin()));
    QObject::connect(ui->precBouton, SIGNAL(clicked()), this, SLOT(goPrec()));
    QObject::connect(ui->suivBouton, SIGNAL(clicked()), this, SLOT(goNext()));
    QObject::connect(ui->confBouton,SIGNAL(clicked()),this,SLOT(goNext()));


}

void Windows::openLogin(){
    Login *fenLogin = new Login(this);//\\alloc OK FREE
    ((QDialog*)fenLogin)->show();
}

void Windows::goPrec(){
    changeIndex(indexPrecedant);
}

void Windows::newSectionGenerique(Section *s){

    goNewSectionGenerique(s);
}

void Windows::codeProduitMenu(Produit *p){
    currentProduit = *p;
    QString s = currentProduit.afficheCode();
    ui->codeLine->setText(s);

    ui->codeLine->setStyleSheet("QLineEdit{color:grey;font-size: 23px;min-width: 300px;max-width: 350px;min-height: 35px;max-height: 30px;}");
    goCodeProduitMenu(p);
}

void Windows::produitMenu(QString s){
    goProduitMenu(s);
}

void Windows::resumeConfMenu(QString marche){
    currentProduit.setCurrentMarche(marche);
    goResumeConfMenu();
}

void Windows::commentMenu(){
    goCom();
}

void Windows::mainSectionMenu(Produit *p){
    currentProduit = *p;
    goMenuSection(p->getName()+"MainMenu",p);
}

void Windows::goNext(){
    if(ui->stack->currentIndex() == 0){
        goProduitListe("ProduitListe");
    }
    else{
        QString codeText = ui->codeLine->text().toUpper();
        QString codeTag = codeText;


        codeTag.truncate(codeText.indexOf('_'));
        if(codeText.isEmpty()){
            QMessageBox::warning(this,"Erreur de saisi","Le champ est vide, veuillez réessayer");
        }
        else{
            if(tagExist(codeTag)){
                //il faut set le produit courrant à celui correspondant au code si celui ci est correcte
                if (retrieveCurrentProduct(codeText)){
                    if(ui->classicBouton->isChecked()){
                        Marche m;//je fais ça pour dire à mon appli que je n'ai pas de marché courrant
                        currentProduit.setCurrentMarche(m);//configuration normale
                        resumeConfMenu("");
                    }
                    else{//Configuration bordereau
                        goMarcheListe("MarcheListe");
                    }
                }
            }
            else{
                QMessageBox::critical(this,"Erreur de Tag du code",
                                      "Tag produit du code inconnu, veuillez réessayer");
            }
        }
    }
}


void Windows::goProduitListe(QString s){
    if (!listMenu.contains(s)){//ajouter ProduitListe si il n'est pas déja instancié
        listMenu <<s;         // on l'ajoute a notre liste des menus
        int index = listMenu.size()-1;      // et on instancie le nvo menu avec les indexs correct
        ProduitListe *prod = new ProduitListe(
                    this,index,this->indexCourant);                      //\\alloc
        ui->stack->addWidget(prod);
    }

    else{//si le menu  existe déja, on récupére son indice (qui correspond)
        ProduitListe *p = (ProduitListe*)ui->stack->widget(indexMenu(s));//a l'indice de la liste, et on met a jour les indexs
        p->setCourPrec(indexMenu(s),this->indexCourant); //avec la méthode hérité setCourPrec.
    }

    setGlobalIndex(indexMenu(s));
    ui->stack->setCurrentIndex(indexMenu(s));

}

void Windows::goMarcheListe(QString s){

    if (!listMenu.contains(s)){
        listMenu <<s;
        int index = listMenu.size()-1;
        MarcheListe *march = new MarcheListe(
                    this,index,this->indexCourant,&currentProduit);                      //\\alloc
        ui->stack->addWidget(march);
    }

    else{//si le menu  existe déja, on récupére son indice (qui correspond)
        MarcheListe *p = (MarcheListe*)ui->stack->widget(indexMenu(s));//a l'indice de la liste, et on met a jour les indexs
        p->setCourPrec(indexMenu(s),this->indexCourant); //avec la méthode hérité setCourPrec.
    }

    setGlobalIndex(indexMenu(s));
    ui->stack->setCurrentIndex(indexMenu(s));
}

void Windows::goCom(){

    if (!listMenu.contains("Commentaire")){
        listMenu <<"Commentaire";
        int index = listMenu.size()-1;
        Commentaire *com = new Commentaire(
                    this,index,this->indexCourant,&currentProduit,dataBase);                      //\\alloc
        ui->stack->addWidget(com);
    }
    else{//si le menu  existe déja, on récupére son indice (qui correspond)
        Commentaire *p = (Commentaire*)ui->stack->widget(indexMenu("Commentaire"));//a l'indice de la liste, et on met a jour les indexs
        p->setCourPrec(indexMenu("Commentaire"),this->indexCourant); //avec la méthode hérité setCourPrec.
    }

    setGlobalIndex(indexMenu("Commentaire"));
    ui->stack->setCurrentIndex(indexMenu("Commentaire"));
}


void Windows::goResumeConfMenu(){

    if (!listMenu.contains("resumeConfiguration")){
        listMenu <<"resumeConfiguration";
        int index = listMenu.size()-1;
        ResumeConfiguration *com = new ResumeConfiguration(
                    this,index,this->indexCourant,&currentProduit,dataBase);                      //\\alloc
        ui->stack->addWidget(com);
    }
    else{//si le menu  existe déja, on récupére son indice (qui correspond)
        ResumeConfiguration *r = (ResumeConfiguration*)ui->stack->widget(indexMenu("resumeConfiguration"));//a l'indice de la liste, et on met a jour les indexs
        r->setCourPrec(indexMenu("resumeConfiguration"),this->indexCourant); //avec la méthode hérité setCourPrec.
        r->affiche();
    }

    setGlobalIndex(indexMenu("resumeConfiguration"));
    ui->stack->setCurrentIndex(indexMenu("resumeConfiguration"));
}

void Windows::goProduitMenu(QString produitName){
    if (!listMenu.contains(produitName)){
        listMenu <<produitName;
        int index = listMenu.size()-1;
        ProduitMenu *prod = new ProduitMenu(
                    this,index,this->indexCourant,produitName);                      //\\alloc
        ui->stack->addWidget(prod);
    }
    else{//si le menu  existe déja, on récupére son indice (qui correspond)
        ProduitMenu *p = (ProduitMenu*)ui->stack->widget(indexMenu(produitName));//a l'indice de la liste, et on met a jour les indexs
        p->setCourPrec(indexMenu(produitName),this->indexCourant); //avec la méthode hérité setCourPrec.
    }

    setGlobalIndex(indexMenu(produitName));
    ui->stack->setCurrentIndex(indexMenu(produitName));
}



void Windows::goMenuSection(QString produitName, Produit *p){

    if (!listMenu.contains(produitName)){
        listMenu <<produitName;
        int index = listMenu.size()-1;
        MainMenuSection *mainMenuSec = new MainMenuSection(
                    this,index,this->indexCourant,p);            //\\alloc
        ui->stack->addWidget(mainMenuSec);
    }
    else{//si le menu  existe déja, on récupére son indice (qui correspond)
        MainMenuSection *menuSection = (MainMenuSection*)ui->stack->widget(indexMenu(produitName));
        menuSection->setCourPrec(indexMenu(produitName),this->indexCourant);
    }
    setGlobalIndex(indexMenu(produitName));
    ui->stack->setCurrentIndex(indexMenu(produitName));

}


void Windows::goCodeProduitMenu(Produit *p){

    if (!listMenu.contains("codeProduitMenu")){
        listMenu <<"codeProduitMenu";
        int index = listMenu.size()-1;
        CodeProduitMenu *codeProdMenu = new CodeProduitMenu(
                    this,index,this->indexCourant,p);            //\\alloc
        ui->stack->addWidget(codeProdMenu);

    }
    else{//si le menu  existe déja, on récupére son indice (qui correspond)
        CodeProduitMenu *codePMenu = (CodeProduitMenu*)ui->stack->widget(indexMenu("codeProduitMenu"));
        codePMenu->setProduit(&currentProduit);
        codePMenu->afficheCode();
        codePMenu->setCourPrec(indexMenu("codeProduitMenu"),this->indexCourant);
    }
    setGlobalIndex(indexMenu("codeProduitMenu"));
    ui->stack->setCurrentIndex(indexMenu("codeProduitMenu"));
}

void Windows::goNewSectionGenerique(Section *s){

    if (!listMenu.contains(s->getNameS())){
        listMenu <<s->getNameS();
        int index = listMenu.size()-1;
        SectionGenerique *Sec = new SectionGenerique(
                    this,index,this->indexCourant,s,&currentProduit);                      //\\alloc
        ui->stack->addWidget(Sec);

    }
    else{//si le menu  existe déja, on récupére son indice (qui correspond)
        SectionGenerique *sec = (SectionGenerique*)ui->stack->widget(indexMenu(s->getNameS()));
        sec->setCourPrec(indexMenu(s->getNameS()),this->indexCourant);
        sec->setCurrentProduit(&currentProduit);
    }
    setGlobalIndex(indexMenu(s->getNameS()));
    ui->stack->setCurrentIndex(indexMenu(s->getNameS()));
}

bool Windows::tagExist(QString tag){

    if (dataBase == NULL)
    {
        QMessageBox::critical(this,"Erreur interne",
                              "La base de données n'a pas été construite");
        return false;
    }
    for (int i = 0 ; i< dataBase->getListeProduit().size() ;i++)
    {
        if(dataBase->getListeProduit().value(i).getTag() == tag){
            return true;
        }
    }
    return false;
}


void Windows::setGlobalIndex(int i){
    this->indexCourant = i;
}

void Windows::changeIndex(int i){
    setGlobalIndex(i);
    ui->stack->setCurrentIndex(i);
}

void Windows::setSectionGenerique(){

    MainMenuSection *menuSection = (MainMenuSection*)ui->stack->widget(indexCourant);
    menuSection->setSection();
    menuSection->affiche();
}


int Windows::indexMenu(QString s){

    if(listMenu.indexOf(s) !=-1 )
        return listMenu.indexOf(s);
    else
        return -1;
}


bool Windows::retrieveCurrentProduct(QString code){
    Produit p;
    if (dataBase == NULL){
        QMessageBox::critical(this,"Erreur interne",
                              "La base de données n'a pas été construite");
        return false;
    }
    QString codeProduitCourrant = currentProduit.getTag()+"_"+currentProduit.readCode();
    if(code == codeProduitCourrant){//si le code produit est celui du code produit courrant
        return true;
    }

    for (int i = 0 ; i< dataBase->getListeProduit().size() ;i++){//on assigne le produit au tag du codeproduit donné en paramétre
        if(dataBase->getListeProduit().value(i).getTag() == code.left(code.indexOf("_"))){
            p = dataBase->getListeProduit().value(i);
        }
    }
    currentProduit = p;
    return buildProduct(code);
}

bool Windows::buildProduct(QString code){
    QString codeProduit = code.mid(code.indexOf("_")+1);//on récupére juste le code sans le tag.

    int codeInconnu = 0;

    for (int i =0; i < codeProduit.size(); i++){
        int codePos = i;
        QString codeval = codeProduit.at(i);//valeur du bit i du code
        int convert = codeval.toInt(0,36);//pour rappel on bosse en base 36.
        codeval = QString::number(convert);

        for(int p=0; p< currentProduit.getListeSection().size();p++){
            Section s = currentProduit.getListeSection().value(p);
            for(int k=0; k< s.getListeDeroul().size();k++){//listes déroulantes
                ListDeroul lD = s.getListeDeroul().value(k);
                for (int j =0; j < lD.getListCode().size();j++){
                    Code c = lD.getListCode().value(j);
                    if(c.getPos() == codePos){
                        if(c.getCodeVal() == codeval ){
                            InfoChamp i;
                            c.setActif(true);
                            i.setCode(c);

                            i.setNomChamp(lD.getName());
                            i.setValChamp(c.getChamp());


                            QList<InfoChamp> lI = s.getListInfoChamp();
                            lI.append(i);

                            s.setListeInfoChamp(lI);
                            QList<Section> lS = currentProduit.getListeSection();
                            lS.replace(p,s);
                            currentProduit.setListSection(lS);

                            codeInconnu++;

                        }

                        else if(c.getChamp() == codeval){//cas ou on les valeurs de la liste dépendent de
                            //la saisie des utilisateurs. "x"
                            InfoChamp i;

                            c.setActif(true);
                            //remplacer les "x"
                            c.setCodeVal(codeval);
                            c.setNomX(codeval);
                            for(int i = 0; i < c.getListOp().size(); i++){
                                Operation op = c.getListOp().value(i);
                                op.setQte(codeval);
                                QList<Operation> lOp = c.getListOp();
                                lOp.replace(i,op);
                                c.setListOp(lOp);
                            }
                            //

                            i.setCode(c);

                            i.setNomChamp(lD.getName());
                            i.setValChamp(c.getChamp());

                            QList<InfoChamp> lI = s.getListInfoChamp();
                            lI.append(i);

                            s.setListeInfoChamp(lI);
                            QList<Section> lS= currentProduit.getListeSection();
                            lS.replace(p,s);
                            currentProduit.setListSection(lS);

                            codeInconnu++;
                        }
                        else if(codeval == "0"){
                            codeInconnu++;
                        }
                    }
                }
            }
            for(int k=0; k< s.getOptCocher().size();k++){//listes optCocher
                OptCocher opt = s.getOptCocher().value(k);
                if(opt.getCode().getPos() == codePos){
                    if(opt.getCode().getCodeVal() == codeval){
                        InfoChamp i;
                        Code c = opt.getCode();
                        c.setActif(true);
                        i.setCode(c);

                        i.setNomChamp(c.getChamp());
                        i.setValChamp("oui");
                        QList<InfoChamp> lI = s.getListInfoChamp();
                        lI.append(i);
                        s.setListeInfoChamp(lI);
                        QList<Section> lS= currentProduit.getListeSection();
                        lS.replace(p,s);
                        currentProduit.setListSection(lS);

                        codeInconnu++;
                    }
                    else if(codeval == "0"){
                        codeInconnu++;
                    }
                }
            }

        }

        if(codeInconnu == 0){
            QMessageBox::critical(this,"Code inconnu",
                                  "Ce code est inconnu, veuillez réessayer ou re configurer le produit");
            return false;
        }
        codeInconnu = 0;
    }
    currentProduit.majRegles(0);
    return true;
}

Windows::~Windows()
{
    delete ui;
}
