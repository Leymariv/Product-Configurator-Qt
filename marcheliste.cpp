#include "marcheliste.h"
#include "ui_marcheliste.h"

MarcheListe::MarcheListe(QWidget *parent,
                         int iC, int iP,Produit *produit) :
    QWidget(parent),
    ui(new Ui::marcheListe),
    PageInterface(parent, iC, iP)
{
    //@ readXMLItem
    ui->setupUi(this);
    currentProduit = produit;
    buildIHM();
    signalAndSlot();

}

void MarcheListe::buildIHM(){
    for(int i = 0 ; i<currentProduit->getListMarche().size();i++){
        ui->marchListe->addItem(currentProduit->getListMarche().
                                value(i).getName());
    }
}

void MarcheListe::destroyIHM(){
    for(int i = 0 ; i<currentProduit->getListMarche().size();i++){
        ui->marchListe->removeItem(0);
    }
}

void MarcheListe::signalAndSlot(){
    QObject::connect(ui->precBouton, SIGNAL(clicked()), this, SLOT(goPrec()));
    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));

    QObject::connect(ui->marchListe,SIGNAL(activated(QString)),
                     this,SLOT(eraseTab()));

    QObject::connect(ui->marchListe,SIGNAL(activated(QString)),
                     this->parent(),SLOT(resumeConfMenu(QString)));

}

void MarcheListe::eraseTab(){
    currentProduit->setCurrentMarche(currentProduit->findMarche
                                     (ui->marchListe->currentText()));
    majCodetProduit();
    ui->marchListe->setCurrentIndex(0);
}
void MarcheListe::goPrec(){
    //destroyIHM();
    emit changeIndex(this->indexPrecedant);
}

void MarcheListe::majCodetProduit(){
    if(currentProduit->getCurrentMarche().getName() != ""){
        QList<Codet> codetsList;
        for(int i =0 ; i < currentProduit->getCurrentMarche().getBaseCommuneCodets().size(); i++){
            //parcours et ajout de tous les codets de la base commune
            Codet codet = currentProduit->getCurrentMarche().getBaseCommuneCodets().value(i);
            if(codet.getAction()== "remove")
                codet.setQte("-"+codet.getQte());
            codetsList.append(codet);
        }

        for (int k = 0; k< currentProduit->getListeSection().size(); k++){
            for (int p = 0; p < currentProduit->getListeSection().value(k).getListInfoChamp().size();p++){
                Code code = currentProduit->getListeSection().value(k).getListInfoChamp().value(p).getCode();
                if(code.getActif()){
                    for (int j = 0; j < code.getListCodet().size(); j++){
                        Codet codet = code.getListCodet().value(j);
                        if(codet.getQte().indexOf("x") != -1){//cas d'une qté variable à mettre a jour avec la qté du code
                            codet.setQteX(code.getCodeVal());
                        }
                        int indice = isPresent(codetsList,codet.getName());
                        if(indice != -1){//le codet est déja présent dans la liste, il faut ajouter leur quantité.
                            Codet cExiste = codetsList.value(indice);
                            int newQte = 0;
                            if(codet.getAction()== "add"){
                                newQte = (codet.getQte().toInt()) + (cExiste.getQte().toInt());
                            }
                            else if(codet.getAction()== "remove"){
                                newQte = (cExiste.getQte().toInt() - (codet.getQte().toInt()));
                            }

                            codet.setQte(QString::number(newQte));
                            //puis le remplacer
                            codetsList.replace(indice,codet);
                        }
                        else//codet non présent dans la liste, on l'ajoute tout simplement.
                            codetsList.append(codet);
                    }
                }
            }

        }
        //parcours des régles dans listRgles
        for (int k = 0 ; k <currentProduit->getListRegle().size();k++){
            RegleCode rg = currentProduit->getListRegle().value(k);

            if(rg.getActif()){
                for (int j = 0; j < rg.getListCodet().size(); j++){
                    Codet codet = rg.getListCodet().value(j);
                    if(codet.getQte().indexOf("x") != -1){//cas d'une qté variable à mettre a jour avec la qté du code
                        codet.setQteX(rg.getNombre());
                    }
                    int indice = isPresent(codetsList,codet.getName());
                    if(indice != -1){//le codet est déja présent dans la liste, il faut ajouter leur quantité.
                        Codet cExiste = codetsList.value(indice);
                        int newQte = 0;
                        if(codet.getAction()== "add"){
                            newQte = (codet.getQte().toInt()) + (cExiste.getQte().toInt());
                        }
                        else if(codet.getAction()== "remove"){
                            newQte = (cExiste.getQte().toInt() - (codet.getQte().toInt()));
                        }

                        codet.setQte(QString::number(newQte));
                        //puis le remplacer
                        codetsList.replace(indice,codet);
                    }
                    else//codet non présent dans la liste, on l'ajoute tout simplement.
                        codetsList.append(codet);
                }

            }
        }

        currentProduit->setListCodet(codetsList);

    }
}

int MarcheListe:: isPresent(QList<Codet> lCodet, QString nameCodet){
    for (int j = 0 ;j< lCodet.size() ; j++){
        if(lCodet.value(j).getName() == nameCodet)
            return j;
    }
    return -1;
}


MarcheListe::~MarcheListe()
{
    delete ui;
}





















