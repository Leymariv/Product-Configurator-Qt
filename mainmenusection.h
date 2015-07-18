#ifndef MAINMENUSECTION_H
#define MAINMENUSECTION_H

#include <QDialog>

#include "pageinterface.h"
#include "produit.h"
#include "sectiongenerique.h"
#include "codeproduitmenu.h"

namespace Ui {
class MainMenuSection;
}

class MainMenuSection : public QDialog, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

signals:
    void changeIndex(int);
    void newSectionGenerique(Section*);
    void codeProduitMenu(Produit *);

public slots:
    void goPrec();
    void goNext();
    void eraseTab();
    void goNewSectionGenerique(QString s);


public:
    explicit MainMenuSection(QWidget *parent = 0,
                             int iC = 0, int iP = 0, Produit *p = 0);

    void setSection();//mettre à jour la section qui vient d'être traitée dans sectionGénérique
    Section getSection(QString s);// retorune l'objet section correspondant au nom donnée en paramétre.
    void affiche();//affiche la configuration et le code produit du produit

    ~MainMenuSection();

private:
    Produit *currentProduit;
    Section currentSection;

    void signalAndSlot();
    Ui::MainMenuSection *ui;
    void buildIHM();//methode d'initialisation de l'IHM de notre main menu




};


#endif // MAINMENUSECTION_H


