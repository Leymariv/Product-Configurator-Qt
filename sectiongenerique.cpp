#include "sectiongenerique.h"
#include "ui_sectiongenerique.h"

SectionGenerique::SectionGenerique(QWidget *parent,
                                   int iC, int iP, Section *s, Produit *p) :
    QWidget(parent),
    ui(new Ui::SectionGenerique),
    PageInterface(parent, iC, iP)
{
    ui->setupUi(this);
    this->section = s;
    this->currentProduit = p;

    signalAndSlot();
    buildIHM();


}


void SectionGenerique::signalAndSlot(){

    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));

    QObject::connect(ui->suivBouton, SIGNAL(clicked()), this, SLOT(goNext()));
    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));

    QObject::connect(this,SIGNAL(setSection()), this->parent(),
                     SLOT(setSectionGenerique()));



}
void SectionGenerique::buildIHM(){

    ui->subTitle->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">"
                          +this->section->getNameS()+"</span></p></body></html>");

    if(!this->section->getListeDeroul().isEmpty()){//build listes déroulantes

        QHBoxLayout *hbox = new QHBoxLayout;
        QVBoxLayout *vbox = new QVBoxLayout;

        for(int i =0; i< this->section->getListeDeroul().size(); i++){
            QLabel *champName = new QLabel("- "+this->section->getListeDeroul().value(i).getName()+":");
            champName->setStyleSheet("QLabel{font-size: 18px;}");
            QComboBox *cbox = new QComboBox;
            cbox->setObjectName(this->section->getListeDeroul().value(i).getName());
            cbox->setStyleSheet("QComboBox{color:grey;border-width: 3px;border-color: white;border-style: solid;border-radius: 7;padding: 3px;font-size: 20px;padding-left: 5px;padding-right: 5px;}");

            cbox->addItem("Choisissez...");

            for(int p=0;p<this->section->getListeDeroul().value(i).
                getListCode().size();p++){

                Code c= this->section->getListeDeroul().value(i).
                        getListCode().value(p);
                cbox->addItem(this->section->getListeDeroul().value(i).
                              getListCode().value(p).getChamp());
            }
            QObject::connect(cbox, SIGNAL(activated(QString)), this, SLOT(getStringCbox(QString)));
            QObject::connect(this, SIGNAL(restoreDefaultList(int)), cbox, SLOT(setCurrentIndex(int)));
            if((this->section->getOptCocher().isEmpty()) &&//réorganiser les widgets de notre fenêtre pour rendre l'affichage plus joli.
                    this->section->getListeDeroul().size()>2){
                vbox->addWidget(champName);
                vbox->addWidget(cbox);
            }
            else{
                hbox->addWidget(champName);
                hbox->addWidget(cbox);
            }
        }
        if((this->section->getOptCocher().isEmpty()) &&
                this->section->getListeDeroul().size()>2){
            ui->groupBoxListe->setLayout(vbox);
        }
        else{
            ui->groupBoxListe->setLayout(hbox);
        }
    }
    else{
        ui->groupBoxListe->setVisible(false);
    }
    if(!this->section->getOptCocher().isEmpty()){//build options à cocher
        QVBoxLayout *vbox = new QVBoxLayout;
        for(int i =0; i< this->section->getOptCocher().size(); i++){
            QCheckBox *cbox = new QCheckBox(this->section->getOptCocher().
                                            value(i).getCode().getChamp());
            cbox->setStyleSheet("QCheckBox{font-size: 18px;}");

            cbox->setObjectName(this->section->getOptCocher().value(i).getCode().getChamp());
            vbox->addWidget(cbox);
            QObject::connect(cbox, SIGNAL(clicked(bool)), this, SLOT(getStringCheckBox(bool)));
            QObject::connect(this, SIGNAL(restoreDefaultOpt(bool)), cbox, SLOT(setChecked(bool)));

        }

        ui->groupBoxOption->setLayout(vbox);
    }

    else{
        ui->groupBoxOption->setVisible(false);
    }

}


void SectionGenerique::goNext(){

    currentProduit->majRegles(0);
    QString mess="";
    if(currentProduit->afficheMessage(mess)){
        QMessageBox::warning(this,"Erreur de configuration",mess);
        restoreDefault();
        return;
    }
    else{
        emit changeIndex(this->indexPrecedant);
        emit setSection();
    }
}

void SectionGenerique::restoreDefault(){
    restoreDefaultList(0);
    restoreDefaultOpt(false);

    QList<InfoChamp> l;
    l= this->section->getListInfoChamp();
    for(int i = 0 ; i < l.size(); i++){//on met a inactif tous les codes de la section
        InfoChamp info =  l.value(i);
        Code c = info.getCode();
        c.setActif(false);
        c.setChamp("");
        c.setCodeVal("");
        info.setCode(c);
        info.setValChamp("non");
        l.replace(i,info);
    }


    this->setSectionProduit(l);
    this->section->setListeInfoChamp(l);

    ui->resumeConf->setText("");
    currentProduit->majRegles(0);

}


void SectionGenerique::getStringCheckBox(bool b){
    int index = rechercheNomChamp(QObject::sender()->objectName());

    InfoChamp i;
    QList<InfoChamp> lInfo = section->getListInfoChamp();

    lInfo.removeAt(index);
    section->setListeInfoChamp(lInfo);

    i.setNomChamp(QObject::sender()->objectName());

    Code c = section->findCodeOptCocher(i.getNomChamp());

    if(b == true){
        i.setValChamp("oui");
        c.setActif(true);
    }
    else{
        i.setValChamp("non");
        c.setActif(false);
    }

    i.setCode(c);
    lInfo.append(i);

    section->setListeInfoChamp(lInfo);

    this->setSectionProduit(lInfo);

    afficheResumeConf();
}

void SectionGenerique::setSectionProduit( QList<InfoChamp> lInfo){
    for(int i = 0; i< currentProduit->getListeSection().size();i++){
        if(currentProduit->getListeSection().value(i).getNameS() == section->getNameS()){
            QList<Section> sectionList = currentProduit->getListeSection();
            Section sec = sectionList.value(i);
            sec.setListeInfoChamp(lInfo);
            sectionList.replace(i,sec);
            this->currentProduit->setListSection(sectionList);
        }
    }
}

void SectionGenerique::getStringCbox(QString valChamp){

    int index = rechercheNomChamp(QObject::sender()->objectName());

    InfoChamp i;
    QList<InfoChamp> lInfo = section->getListInfoChamp();

    lInfo.removeAt(index);
    section->setListeInfoChamp(lInfo);

    i.setNomChamp(QObject::sender()->objectName());


    Code c = section->findCodeListDeroul(i.getNomChamp(),valChamp);

    if(valChamp =="Choisissez..."){//cas ou on a rien sélectionné
        i.setValChamp("non");
        c.setActif(false);
    }
    else{
        if(c.getCodeName()=="ERR"){
            QMessageBox::warning(this,"Code introuvable","Impossible de trouver le code "+
                                 i.getNomChamp());
        }

        c.setActif(true);


        if(c.getCodeVal()=="x"){

            c.setCodeVal(valChamp);
            c.setNomX(valChamp);
            for(int i = 0; i < c.getListOp().size(); i++){
                Operation op = c.getListOp().value(i);
                op.setQte(valChamp);
                QList<Operation> lOp = c.getListOp();
                lOp.replace(i,op);
                c.setListOp(lOp);
            }
        }

        i.setValChamp(valChamp);
    }
    i.setCode(c);
    lInfo.append(i);
    section->setListeInfoChamp(lInfo);
    this->setSectionProduit(lInfo);
    afficheResumeConf();
}


void SectionGenerique:: afficheResumeConf(){
    QString resumeConf="";
    if(!section->getListInfoChamp().isEmpty()){
        for(int i = 0; i < section->getListInfoChamp().size();i++){
            if(section->getListInfoChamp().value(i).getValChamp() == "oui"){

                resumeConf += "- "+section->getListInfoChamp().value(i).getNomChamp()+
                        ": \u2611\n\n";
            }
            else if (section->getListInfoChamp().value(i).getValChamp() == "non"){}

            else{
                resumeConf += "- "+section->getListInfoChamp().value(i).getNomChamp()+
                        ": "+section->getListInfoChamp().value(i).getValChamp()+"\n\n";
            }
        }
    }
    ui->resumeConf->setText(resumeConf);
}

int SectionGenerique::rechercheNomChamp(QString name){
    if(!this->section->getListInfoChamp().isEmpty()){
        for (int i=0; i <this->section->getListInfoChamp().size();i++){
            if(this->section->getListInfoChamp().value(i).getNomChamp() == name){
                return i;
            }
        }
    }
    return -1;
}


SectionGenerique::~SectionGenerique()
{
    delete ui;
}
