#include "produitliste.h"
#include "ui_produitliste.h"

ProduitListe::ProduitListe(QWidget *parent, int iC, int iP) :
    QWidget(parent),
    ui(new Ui::ProduitListe),
    PageInterface(parent, iC,iP)
{
    ui->setupUi(this);

    Windows *w = (Windows*)parent;//récupérer l'objet windows pour avoir accées a la liste des produits
    ui->produitsListe->addItem("Choisissez...");
    for(int i=0; i < w->getData()->getListeProduit().size();i++){

        QString champ = w->getData()->getListeProduit().value(i).getName();
        ui->produitsListe->addItem(champ);
    }

    signalAndSlot();

}

void ProduitListe::signalAndSlot(){

    QObject::connect(ui->precBouton, SIGNAL(clicked()), this, SLOT(goPrec()));
    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(), SLOT(changeIndex(int)));

    QObject::connect(ui->produitsListe,SIGNAL(activated(QString)),
                     this,SLOT(callProduitMenu(QString)));

    QObject::connect(this,SIGNAL(goProduitMenu(QString)),
                     this->parent(),SLOT(produitMenu(QString)));

    QObject::connect(ui->produitsListe,SIGNAL(activated(QString)),
                     this,SLOT(eraseTab()));

}

void ProduitListe::eraseTab(){//permet de remettre l'affichage de la combobox vide

    ui->produitsListe->setCurrentIndex(0);
}

void ProduitListe::goPrec(){

    emit changeIndex(this->indexPrecedant);

}

void ProduitListe::callProduitMenu(QString s){
    if(s=="Choisissez...")
        return;
    else
        emit goProduitMenu(s);
}


ProduitListe::~ProduitListe()
{
    delete ui;
}
