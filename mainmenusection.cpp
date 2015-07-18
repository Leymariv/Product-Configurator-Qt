#include "mainmenusection.h"
#include "ui_mainmenusection.h"

MainMenuSection::MainMenuSection(QWidget *parent,
                                 int iC, int iP, Produit *p) :
    QDialog(parent),
    ui(new Ui::MainMenuSection),
    PageInterface(parent,iC,iP)
{
    ui->setupUi(this);
    this->currentProduit = p;
    buildIHM();
    signalAndSlot();

}

void MainMenuSection::signalAndSlot(){

    QObject::connect(ui->precBouton, SIGNAL(clicked()), this, SLOT(goPrec()));
    QObject::connect(ui->suivBouton, SIGNAL(clicked()), this, SLOT(goNext()));
    QObject::connect(this,SIGNAL(codeProduitMenu(Produit*)), this->parent(),
                     SLOT(codeProduitMenu(Produit *)));

    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));

    QObject::connect(ui->listSection,SIGNAL(activated(QString)),
                     this,SLOT(goNewSectionGenerique(QString)));

    QObject::connect(this,SIGNAL(newSectionGenerique(Section*)), this->parent(),
                     SLOT(newSectionGenerique(Section*)));

    QObject::connect(ui->listSection,SIGNAL(activated(QString)),
                     this,SLOT(eraseTab()));


}

void MainMenuSection::goPrec(){
    emit changeIndex(this->indexPrecedant);
}


void MainMenuSection::goNewSectionGenerique(QString s){

    if(s == "Choisissez...")
        return;
    else{
        this->currentSection = this->getSection(s);
        emit newSectionGenerique(&(this->currentSection));
    }
}

void MainMenuSection::goNext(){
    currentProduit->majRegles(0);
    QString mess="";
    if(currentProduit->afficheMessage(mess)){
        QMessageBox::warning(this,"Erreur de configuration",mess);
        return;
    }
    else
        emit codeProduitMenu(this->currentProduit);
}


Section MainMenuSection::getSection(QString sectionName){
    Section s;
    for(int i = 0; i< currentProduit->getListeSection().size();i++){
        s = this->currentProduit->getListeSection().at(i);
        if(s.getNameS() == sectionName)
            return this->currentProduit->getListeSection().at(i);
    }
    QMessageBox::critical(this, "Erreur Interne","getSection : Section introuvable");
    return s;
}


void MainMenuSection::setSection(){
    for(int i = 0; i< currentProduit->getListeSection().size();i++){
        Section s = this->currentProduit->getListeSection().value(i);
        if(s.getNameS() == currentSection.getNameS()){

            QList<Section> sectionList = this->currentProduit->getListeSection();
            Section sec = sectionList.value(i);
            sec.setListeInfoChamp(currentSection.getListInfoChamp());
            sectionList.replace(i,sec);
            this->currentProduit->setListSection(sectionList);
        }
    }
}



void MainMenuSection::eraseTab(){//permet de remettre l'affichage de la combobox vide

    ui->listSection->setCurrentIndex(0);
}


void MainMenuSection:: buildIHM(){

    ui->subTitle->setText("<html><head/><body><p align=\"left\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">"
                          +currentProduit->getName()+"</span></p></body></html>");
    if (currentProduit->getNbSection() == 0){
        QMessageBox::warning(this, "Attention","Ce produit ne comporte aucune section");
        return;
    }
    else{
        QString resume = "";
        ui->listSection->addItem("Choisissez...");
        for (int i =0; i < currentProduit->getNbSection();i++){

            resume += "<html><head/><body><p align=\"left\"><span style=\" font-size:12pt; font-weight:600; color:#5d5d5d;\">\u2022"
                    + currentProduit->getListeSection().value(i).getNameS()+"</span></p></body></html>";
            ui->listSection->addItem(currentProduit->getListeSection().value(i).getNameS());
        }
        ui->resumeConf->setText(resume);
        ui->codeProduit->setText("<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">Code Produit : "+
                                 currentProduit->afficheCode()+" </span></p></body></html>");
    }
}




void MainMenuSection::affiche(){
    ui->resumeConf->setText(currentProduit->resumeConfNormale());
    ui->codeProduit->setText("<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">Code Produit : "+
                             currentProduit->afficheCode()+" </span></p></body></html>");

    ui->suivBouton->setStyleSheet( "#suivBouton{color: orange;background-color: white;}");
    ui->suivBouton->setEnabled(true);
}


MainMenuSection::~MainMenuSection()
{
    delete ui;
}

