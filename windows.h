#ifndef WINDOWS_H
#define WINDOWS_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QLayout>
#include <QVBoxLayout>
#include <QList>

#include "ui_Windows.h"
#include "login.h"
#include "marcheliste.h"
#include "produitliste.h"
#include "pageinterface.h"
#include "commentaire.h"
#include "mainmenusection.h"
#include "produitmenu.h"
#include "data.h"
#include "produit.h"
#include "sectiongenerique.h"
#include "resumeconfiguration.h"

namespace Ui {
class Windows;
}

class Windows : public QDialog, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

public slots:
    void openLogin();//open a  qdialog with the login form
    void goPrec();//go to the previous menu from menu 0 or 1
    void goNext();//go to next menu from page 0 and 1
    void changeIndex(int);//change the current index of our stack
    void setSectionGenerique();//pour afficher le résumé de la configuration, il nous faut metre a jour la section
    void commentMenu();//instanciate or simply change the index of our stack to go to comment Menu
    void mainSectionMenu(Produit *p);//instanciate or simply change the index of our stack to go to mainSectionMenu
    void produitMenu(QString s);//instanciate or simply change the index of our stack to go to produitMenu
    void newSectionGenerique(Section *s);//instanciate or simply change the index of our stack to go to sectionGenerique
    void codeProduitMenu(Produit *p);//instanciate or simply change the index of our stack to go to sectionGenerique
    void resumeConfMenu(QString marche);//instanciate or simply change the index of our stack to go to resumeConfMenu

public:
    explicit Windows(QWidget *parent = 0,
                     int iC = 0, int iP = 0);
    ~Windows();

    Data* getData(){return this->dataBase;}

private:
    Ui::Windows *ui;
    QList<QString> listMenu;
    Data *dataBase;
    Produit currentProduit;

    void signalAndSlot();//initialise les signaux et slots
    void setGlobalIndex(int i); //permet de mettre a jour l'index courrant en fonction de la page active
    int indexMenu(QString s);//return l'index du menu passé en paramétre
    bool tagExist(QString tag);//revoie vrai si le tag donné en paramétre existe dans
                               //la liste des produits. Met à jour le produit courrant pour interprétation du code produit.

    //permet d'instancier ou de passer au menu
    bool retrieveCurrentProduct(QString code);//cette fonction met à jour le produit courrant au produit
                                        //correspondant au code produit entrée en paramétre. Elle retourne true si le code produiit est correct
    bool buildProduct(QString code);//cette méthode set les attributs du produit en lisant le code produit
                                    //afin de créer le produit du code produit passé en paramétre.Elle retourne true si le code produiit est correct
                                    //si un code est impossible, l'appli devra nous le dire.

    //Sont appelés pour instancier les classes correspondantes. J'ai fait cela car selon mon architecture,
    //SEULE la classe Windows peut instancier d'autres classes.
    void goProduitListe(QString);
    void goMarcheListe(QString);
    void goCom();
    void goMenuSection(QString,Produit*);
    void goProduitMenu(QString produitName);
    void goNewSectionGenerique(Section *s);
    void goCodeProduitMenu(Produit *p);
    void goResumeConfMenu();


};

#endif // WINDOWS_H
