#ifndef MARCHELISTE_H
#define MARCHELISTE_H

#include <QWidget>
#include <QMessageBox>

#include "pageinterface.h"
#include "produit.h"
#include "windows.h"

namespace Ui {
class marcheListe;
}

class MarcheListe : public QWidget, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

signals:
    void changeIndex(int);

public slots:
  void goPrec();
  void eraseTab();

public:
    explicit MarcheListe(QWidget *parent = 0,
                         int iC = 0, int iP = 0,Produit *produit = 0);
    ~MarcheListe();


private:
    Ui::marcheListe *ui;
    void signalAndSlot();
    void buildIHM();//construit l'ihm du menu
    void destroyIHM();//enleve les menus déroulants
    void majCodetProduit();//Cette fonction met à jour la liste des codets en fonction des CODES et des REGLES
                         //que l'utilisateur à sélectionné dans la liste des infochamps
    int isPresent(QList<Codet> lCodet, QString nameCodet);//retourne l'indice du codet de la liste des codet si celui ci existe
                                                        //sinon retourne -1.
                                                       //Fonction utiliser pour merger notre liste de codet si deux codets on
                                                        //le même nom, on ajoute leurs qauntités

     Produit *currentProduit;
};

#endif // MARCHELISTE_H
