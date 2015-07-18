#ifndef DATA_H
#define DATA_H

#include <QDialog>
#include <QList>
#include <QtXml>
#include <QApplication>
#include <QMessageBox>

#include "produit.h"
#include "section.h"
#include "optcocher.h"
#include "listderoul.h"
#include "marche.h"
#include "codet.h"
#include "frais.h"
#include "mdo.h"
#include "pathConfig.h"


class Data : public QDialog
{
    Q_OBJECT
public:


    Data();
    QList<Produit> getListeProduit();
    QString getPathXML(){return this->pathXML;}
    QString getPathFiche(){return this->pathFiche;}
    QString getPathSyst(){return this->pathSyst;}
    QString getPathBA(){return this->pathBA;}
    QString getPathIni(){return this->pathIni;}
    QString getpathSynchro(){return this->pathSynchro;}

    QString getVersionConfXML(){return this->versionConfXML;}

    QList<Frais> getListFrais(){return this->listFrais;}
    QList<Mdo> getListMdo(){return this->listMdo;}

    ~Data();

private:

    QList<Produit> listP;//liste de tous les produits.

    QString pathXML;
    QString pathFiche;
    QString pathSyst;
    QString pathBA ;
    QString pathIni;
    QString pathSynchro;
    QString versionConfXML;


    void initializePaths();//Initialise tous les paths utilisés dans mon application via le fichier "path.ini". C'est la première chose que fera notre appli
    void retrieveFolder();//copie les dossiers du réseau, en local sur l'ordinateur, à l'endroit de l'application. Cette fonction crée "retrieve.bat" qui va ensuite être appelé via un appel system
    void cmdDos(QString commande);//executer la cmd donnée en paramétre


    void readXml(QString file);//permet d'insatnacier un objet Dqom et tt ce qui va puis appel les fcts build
    QString VerifieXmlRead(QString champ, //Permet de vérifier qu'on a bien lu les champsdu xml.
                           QDomElement element,QString file); //si le fichier est mal conçu on le saura
    double VerifieXmlDouble(QString champ, //Même fonctionalitée, mais en plus Permet de remplacer le caractére "," par "." nécessaire pour la conversion en double.
                            QDomElement element,QString file);//en effet, qt ne sait pas convertir 3,12 en double, il sait convertir 3.12 en double.
    QString VerifieXmlOperation(QString champ, //Permet de vérifier qu'on a bien lu un des champs "+","-","*" ou "/".
                                QDomElement element,QString file);
    QString VerifieXmlComparaison(QString champ, //Permet de vérifier qu'on a bien lu un des champs ">","<","="
                                QDomElement element,QString file);
    QString VerifieXmlOperande(QString champ, //Permet de vérifier qu'on a bien lu un des champs "ET","OU"
                                QDomElement element,QString file);
    void buildData(QDomElement dom_element, QString file);//sert a lire le xml conf.xml ainsi qu'à construire la liste de main d'oeuvre et la liste des frais
    void buildIndexProduit(QDomElement dom_element, QString file);//Permet de lire dans le fichier IndexProduits.xml l'ensemble des produits, ainsi que leurs tags. De cette façon on aura accés au dossier ou lire
    //les xmls de chaque produit. Nom du dossier = TAG.

    void buildDataProduit(QDomElement dom_element, QString file);//permet de remplir la liste de produit en lisant le fichier
    //xml rentré en paramétre.
    void buildDataNomenclature(QDomElement dom_element, QString file);//permet de remplir pour chaque produit sa nomenclature
    //xml rentré en paramétre.
    void buildDataMarche(QDomElement dom_element, QString file);//Permet de remplir pour chaque produit, la liste de ses marchés, et des
    //codets associés à chacun de ces marchés.
    void buildDataOP(QDomElement dom_element, QString file);//Permet de remplir pour chaque produit, la liste des opérations associés
    //à tous les codes du produit.
    Produit findProduit(QString name);//renvoie un produit de la liste des produits selon son nom
     bool estPresent(QString name);//renvoie true si le produit a déja été enregistré
    bool findCodeList(QList<Code> l ,QString codeName);//savoir si un code existe déjà dans la liste des codes

    QList<Frais> listFrais;
    QList<Mdo> listMdo;

};

#endif // DATA_H
