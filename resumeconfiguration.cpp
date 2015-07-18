#include "resumeconfiguration.h"
#include "ui_resumeconfiguration.h"

ResumeConfiguration::ResumeConfiguration(QWidget *parent,
                                         int iC, int iP,
                                         Produit *produit,
                                         Data *d) :
    QWidget(parent),
    ui(new Ui::ResumeConfiguration),
    PageInterface(parent,iC,iP)
{
    ui->setupUi(this);
    currentProduit = produit;
    database = d;
    signalAndSlot();
    affiche();
}

ResumeConfiguration::~ResumeConfiguration()
{
    delete ui;
}

void ResumeConfiguration::signalAndSlot(){
    QObject::connect(ui->precBouton, SIGNAL(clicked()), this, SLOT(goPrec()));
    QObject::connect(ui->suivBouton,SIGNAL(clicked()), this->parent(),
                     SLOT(commentMenu()));
    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));

}

void ResumeConfiguration::goPrec(){
    emit changeIndex(this->indexPrecedant);
}

void ResumeConfiguration::affiche(){
    afficheMdO();
    afficheNomenclature();
    afficheConf();

}

void ResumeConfiguration::afficheNomenclature(){
    ui->resumeNom->setText(currentProduit->resumeNomenclature());
    ui->prixTotNom->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">Prix Nomenclature: "
                         +QString::number(currentProduit->getPrixTotNomFG()+
                                          currentProduit->getPrixTotNomAffaire())+" €</span></p></body></html>");
}

void ResumeConfiguration::afficheMdO(){
ui->resumeMdo->setText(currentProduit->resumeMdo());
ui->prixTotMdo->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">Prix Main d'oeuvre: "
                     +QString::number(currentProduit->getPrixTotMdo())+" €</span></p></body></html>");
}

void ResumeConfiguration::afficheConf(){
    ui->subTitle->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">"
                          +currentProduit->afficheCode()+"</span></p></body></html>");

    ui->prixTot->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">Prix de revient chargé: "
                         +QString::number(calculPrixRevientCharge())+
                         " €</span></p></body></html>");

    if(currentProduit->getCurrentMarche().getName() == "")//cas d'une configuration normale
        ui->resumeConf->setText(currentProduit->resumeConfNormale());
    else//cas d'une configuration bordereau
        ui->resumeConf->setText(currentProduit->resumeConfBordereau());
}

double ResumeConfiguration::calculPrixRevientCharge(){
    double pourcentageFraisDSS = database->getListFrais().value(0).getPourcentage()/100;
    double pourcentageFraisFin = database->getListFrais().value(1).getPourcentage()/100;
    double pourcentageFraisDir = database->getListFrais().value(2).getPourcentage()/100;
    double pourcentageFraisGen = database->getListFrais().value(3).getPourcentage()/100;
    double prixTotalSansRevient = currentProduit->getPrixTotNomFG()+
            currentProduit->getPrixTotNomAffaire()+currentProduit->getPrixTotMdo();

    double prixCharge = prixTotalSansRevient+ pourcentageFraisGen * (currentProduit->getPrixTotNomFG()+
                                             currentProduit->getPrixTotNomAffaire());
    double fDSS =  pourcentageFraisDSS*prixCharge;
    double fFin =  pourcentageFraisFin*prixCharge;
    double fDir =  pourcentageFraisDir*prixCharge;
    prixCharge += fDSS+fFin+fDir;
    return prixCharge;
}
