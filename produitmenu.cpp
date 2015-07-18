#include "produitmenu.h"
#include "ui_produitmenu.h"



ProduitMenu::ProduitMenu(QWidget *parent, int iC, int iP, QString name) :
    QWidget(parent),
    ui(new Ui::ProduitMenu),
    PageInterface(parent,iC,iP)

{
    ui->setupUi(this);
    signalAndSlot();

    this->produitName = name;

    this->p = findProduit(produitName);

    ui->subTitle->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">Informations "
                          +p.getName()+"</span></p></body></html>");
    ui->descriptionItem->setText(p.getText());
   // ui->descriptionItem->setText(p.affichInfos());
}

void ProduitMenu::signalAndSlot(){
    QObject::connect(ui->precBouton, SIGNAL(clicked()), this, SLOT(goPrec()));
    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));

    QObject::connect(ui->suivBouton,SIGNAL(clicked()),
                     this,SLOT(goMainSectionMenu()));
    QObject::connect(this,SIGNAL(mainSectionMenu(Produit*)), this->parent(),
                     SLOT(mainSectionMenu(Produit*)));

    QObject::connect(ui->image, SIGNAL(clicked()), this, SLOT(openImage()));
    QObject::connect(ui->ficheProduit, SIGNAL(clicked()), this, SLOT(openPDF()));

}

void ProduitMenu::goMainSectionMenu(){
    emit mainSectionMenu(&(this->p));
}

void ProduitMenu::goPrec(){

    emit changeIndex(this->indexPrecedant);
}

void ProduitMenu::openImage(){

    if(!QFile::exists(p.getLienImg())){
        QMessageBox::critical(this, "Erreur ouverture du fichier",
                              "Impossible d'ouvrir le fichier:\n\n"+p.getLienImg()+
                              "\n\nPensez à vérifier Produit.xml");
        return;
    }
    else{
        QDesktopServices::openUrl(QUrl::fromLocalFile(p.getLienImg()));
    }
}

void ProduitMenu::openPDF(){

    if(!QFile::exists(p.getLienPdf())){
        QMessageBox::critical(this, "Erreur ouverture du fichier",
                              "Impossible d'ouvrir le fichier:\n\n"+p.getLienPdf()+
                              "\n\nPensez à vérifier Produit.xml");
        return;
    }
    else QDesktopServices::openUrl(QUrl::fromLocalFile(p.getLienPdf()));
}

Produit ProduitMenu::findProduit(QString nProduit){
    Windows *w = (Windows*)this->parent();

    Produit p;

    for(int i=0; i < w->getData()->getListeProduit().size();i++){
        p = w->getData()->getListeProduit().value(i);
        if(p.getName() == nProduit)
            return p;
    }
    QMessageBox::critical(this, "Erreur liste produit","Impossible de trouver le produit dans la liste des produits");
    this->close();
    return p;
}

ProduitMenu::~ProduitMenu()
{
    delete ui;
}
