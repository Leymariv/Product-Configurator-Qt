#ifndef SECTIONGENERIQUE_H
#define SECTIONGENERIQUE_H

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>

#include "pageinterface.h"
#include "section.h"
#include "infochamp.h"
#include "windows.h"

namespace Ui {
class SectionGenerique;
}

class SectionGenerique : public QWidget, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

signals:
    void changeIndex(int);
    void setSection();
    void restoreDefaultList(int);
    void restoreDefaultOpt(bool);

public slots:
   // void goPrec();
    void goNext();
    void getStringCbox(QString valChamp);//permet de mettre a jour la valeur du champ de la combobox, aprés interaction de l'utilisateur.
    void getStringCheckBox(bool b);//permet de mettre a jour la valeur du champ de la check box, aprés interaction de l'utilisateur.



public:
    explicit SectionGenerique(QWidget *parent = 0,
                              int iC = 0, int iP = 0, Section *s = 0, Produit *p=0 );

    void setCurrentProduit(Produit *p){this->currentProduit = p;}

    ~SectionGenerique();

private:
    Ui::SectionGenerique *ui;
    Section *section;
    Produit *currentProduit;

    int rechercheNomChamp(QString name);//retourne l'index de la liste listInfoChamp correspondant au nom du champ passé en paramétre

    void signalAndSlot();
    void buildIHM();//permet de construire l'ihm pour la section concernée.
    void afficheResumeConf();//affiche le résumé de la configuration.
    void setSectionProduit(QList<InfoChamp> lInfo);//Met a jour la liste d'infochamp du produit pour chaque sectionsINDISPENSABLE POUR METTRE A JOUR NOTRE PRODUIT, ET METTRE A JOUR LES REGLES POUR AFFICHER NOTRE MESSAGE.
    void restoreDefault();//réinitialise toutes les listes déroulantes, options à cocher, et listes des infos champs. Est appelé en cas d'affichage d'un message suite à une erreur de configuration.
};

#endif // SECTIONGENERIQUE_H
