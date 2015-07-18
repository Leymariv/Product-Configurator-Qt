#include "codeproduitmenu.h"
#include "ui_codeproduitmenu.h"

CodeProduitMenu::CodeProduitMenu(QWidget *parent,
                                 int iC, int iP,Produit *p) :
    QWidget(parent),
    ui(new Ui::CodeProduitMenu),
    PageInterface(parent,iC,iP)
{
    ui->setupUi(this);
    this->currentProduit = p;
    signalAndSlot();
    afficheCode();
}

CodeProduitMenu::~CodeProduitMenu()
{
    delete ui;
}

void CodeProduitMenu::signalAndSlot(){
    QObject::connect(ui->precBouton, SIGNAL(clicked()), this, SLOT(goPrec()));
    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));
    QObject::connect(ui->mainMenuBouton, SIGNAL(clicked()), this, SLOT(goMainMenu()));
    QObject::connect(ui->codeBouton,SIGNAL(clicked()), this->parent(),
                     SLOT(openLogin()));
}

void CodeProduitMenu::goPrec(){

   emit changeIndex(this->indexPrecedant);
}

void CodeProduitMenu::goMainMenu(){
   emit changeIndex(0);
}

void CodeProduitMenu::afficheCode(){
    ui->codeProduit->setText("<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#5d5d5d;\">Code Produit : "+
                             currentProduit->afficheCode()+" </span></p></body></html>");
}


