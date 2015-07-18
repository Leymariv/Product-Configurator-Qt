#ifndef COMMENTAIRE_H
#define COMMENTAIRE_H

#include <QWidget>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QDesktopServices>

#include "pageinterface.h"
#include "produit.h"
#include "data.h"
#include "pathConfig.h"

namespace Ui {
class Commentaire;
}

class Commentaire : public QWidget ,public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

signals:
    void changeIndex(int);

public slots:
    void goPrec();
    void goNext();
public:
    explicit Commentaire(QWidget *parent = 0,
                         int iC = 0, int iP = 0,
                         Produit *produit=0,
                         Data *d=0);
    ~Commentaire();

private:
    void signalAndSlot();
    void zipXlsx();//rezipp le xlsx
    void editFile(QString fileSrc, QString fileDest);//édite les fichiers nécessaires à la modification de notre xlsx en appellant des focntions
    bool generateReplaceVBS();//créer le fichier replace.vbs
    QString generateFillNomenclatureFG();//renvoie la string vbs à mettre dans notre script .vbs pour les composants FG
    QString generateFillNomenclatureAffaire();//renvoie la string vbs à mettre dans notre script .vbs pour les composants Affaire
    QString generateFillBordereau();//renvoie la string vbs à mettre dans notre script .vbs pour les codets
    void cmdDos(QString commande);//fonction qui permet d'effectuer la commandee dos passé en paramétre.
    QString updatePath(QString path);//sert à changer les "/" de sens pour être utilisé par le cmd

    Ui::Commentaire *ui;

    Produit *currentProduit;
    Data *database;
    QString pathSyst;
    QString pathBA;

};

#endif // COMMENTAIRE_H
