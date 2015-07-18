#ifndef RESUMECONFIGURATION_H
#define RESUMECONFIGURATION_H

#include <QWidget>
#include "pageinterface.h"
#include "produit.h"
#include "data.h"

namespace Ui {
class ResumeConfiguration;
}

class ResumeConfiguration : public QWidget, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

signals:
    void changeIndex(int);

public slots:
    void goPrec();

public:
    explicit ResumeConfiguration(QWidget *parent = 0,
                                 int iC = 0, int iP = 0,
                                 Produit *produit = 0,
                                 Data *d=0);

    void setProduit(Produit *p){this->currentProduit = p;}//sert a set le current produit depuis windows
    void affiche();//Réalise l'affichage des 3 onglets
    ~ResumeConfiguration();

private:
    Ui::ResumeConfiguration *ui;
    void signalAndSlot();

    void afficheNomenclature();//affichage de la nomenclature
    void afficheMdO();//affichage de la main d'oeuvre
    void afficheConf();//affichage de la configuration
    double calculPrixRevientCharge();//calcul du prix de revient chargé selon le fichier BA.xlsx (je n'ai rien inventé)

    Produit *currentProduit;
    Data *database;
};

#endif // RESUMECONFIGURATION_H
