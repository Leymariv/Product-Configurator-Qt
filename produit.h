#ifndef PRODUIT_H
#define PRODUIT_H

#include <QDialog>
#include <QList>
#include <QtXml>
#include <QApplication>
#include <QMessageBox>

#include "section.h"
#include "composant.h"
#include "composantaffaire.h"
#include "composantfg.h"
#include "reglecode.h"
#include "marche.h"
#include "operation.h"

class Produit
{

public:

    Produit();
    Produit(QString n, QString i , QString p, QString t);
    ~Produit();

    QString getName(){return this->name;}
    QString getLienPdf(){return this->lienPdf;}
    QString getLienImg(){return this->lienImg;}
    QString getTag(){return this->tag;}
    QString getText(){return this->text;}
    QString getVersionProduitXML(){return this->versionProduitXML;}
    QString getVersionNomenclatureXML(){return this->versionNomenclatureXML;}
    QString getVersionMarcheXML(){return this->versionMarcheXML;}
    QString getVersionOperationXML(){return this->versionOperationXML;}
    Marche getCurrentMarche(){return this->marcheCourrant;}
    QList<Section> getListeSection(){return this->listSection;}
    QList<Composant> getListeComposant(){return this->listComposant;}
    QList<Composant> getListeComposantFG(){return this->listComposantFG;}
    QList<Composant> getListeComposantAffaire(){return this->listComposantAffaire;}
    QList<Composant> getBaseCommuneComposants(){return this->baseCommuneComposants;}
    QList<Operation> getBaseCommuneOperations(){return this->baseCommuneOperations;}
    QList<RegleCode> getListRegle(){return this->listRegle;}
    QList<Marche> getListMarche(){return this->listMarche;}
    int getNbSection(){return this->nbSection;}
    int getQte(){return this->qte;}
    QList<QString> getCodeProduit(){return this->codeProduit;}
    QList<Codet> getListCodets(){return this->listCodet;}
    QList<Operation> getListOperation(){return this->listOperation;}
    double getPrixTotNomFG(){return this->prixTotNomFG;}
    double getPrixTotNomAffaire(){return this->prixTotNomAffaire;}
    double getPrixTotMdo(){return this->prixTotMdo;}
    double getPrixVenteMarche(){return this->prixVenteMarche;}
    double getNbHCdp(){return this->nbHCdp;}
    double getNbHTech(){return this->nbHTech;}
    double getNbHOuv(){return this->nbHOuv;}

    void setListSection(QList<Section> l){this->listSection = l;}
    void setListComposant(QList<Composant> l){this->listComposant = l;}
    void setListComposantFG(QList<Composant> l){this->listComposantFG = l;}
    void setListComposantAffaire(QList<Composant> l){this->listComposantAffaire = l;}
    void setBaseCommuneComposants(QList<Composant> l){this->baseCommuneComposants = l;}
    void setBaseCommuneOperations(QList<Operation> l){this->baseCommuneOperations = l;}
    void setName(QString n){this->name = n;}
    void setCurrentMarche(Marche n){this->marcheCourrant = n;}
    void setTag(QString n){this->tag = n;}
    void setLienImg(QString i){this->lienImg = i;}
    void setLienPdf(QString p){this->lienPdf = p;}
    void setText(QString t){this->text = t;}
    void setNbSection(int nbS){this->nbSection = nbS;}
    void setQte(int q){this->qte = q;}
    void setCodeProduit(QList<QString> c){this->codeProduit = c;}
    void setListRegle(QList<RegleCode> c){this->listRegle = c;}
    void setListMarche(QList<Marche> c){this->listMarche = c;}
    void setListCodet(QList<Codet> c){this->listCodet = c;}
    void setListOperation(QList<Operation> c){this->listOperation = c;}
    void setVersionProduitXML(QString s){this->versionProduitXML = s;}
    void setVersionNomenclatureXML(QString s){this->versionNomenclatureXML = s;}
    void setVersionMarcheXML(QString s){this->versionMarcheXML = s;}
    void setVersionOperationXML(QString s){this->versionOperationXML = s;}


    QString resumeConfNormale();//retourne la string de la configuration compléte du produit lorsque la configuration est normale
    QString resumeConfBordereau();//retourne la string de la configuration compléte du produit lorsque la configuration est en bordereau
    QString resumeNomenclature();//methode d'affichage de la nomenclature compléte, base+ nom
    QString resumeCodeProduit();//methode d'affichage des codes produits
    QString resumeMdo();//methode d'affichage de la main d'oeuvre
    Composant findComposant(QString id);//renvoie un composant de la liste des composant
    Operation findOperation(QString id);//renvoie une opération de la liste des opération
    QString affichInfos();// retorune la string de toutes les infos du xml Produits.xml, FONCTION DE TEST A EFFACER
    Code findCodeProduit(QString name);//retourne le code produit du produit en fonction de son nom.
    RegleCode findRegle(QString name);//retourne la régle du produit en fonction de son nom.
    Code findCodeInfoChamp(QString name);//retourne le code produit de la liste des infoschamp en fonction de son nom.
    void mergeLists();//merge les listes de composants.
    void replaceCode(QString name, Code c);//remplace le code produit par un autre (setter)
    void replaceRegle(RegleCode r);//remplace le code produit par un autre (setter)
    QString afficheCode();//met a jour la liste de qstring du code produit
    QString readCode();//retourne la string du code produit
    void majRegles(int indice);//met a jour l'état de la régle: Soit elle est active
                    //(les codes qui la constituent sont actifs) soit elle reste inactive
    //l'indice sert à rappeler la fonction 1 fois à la fin pour être sûre que les régles ont été maj une premiere fois
    Marche findMarche(QString s);
    bool afficheMessage(QString &message);//parcours les régles, regarde ci elles sont satisfaites, et si tel est le cas, affiche un message et return true.
                           //Si aucun message n'est a affiché, on a pas de prolème et on retourne true.


private:


    QString name;//nom du produit
    QString lienImg;//lien vers l'image du produit
    QString lienPdf;//lien vers le pdf du produit
    QString text;//Description du produit
    QString tag;//Tag du nom du produit dans le code produit (void Produit.xml)
    QString versionProduitXML;
    QString versionNomenclatureXML;
    QString versionMarcheXML;
    QString versionOperationXML;
    Marche marcheCourrant;//nom du marché sélectioné, ce champ est vide si aucun marché n'a été sélectionné
    int nbSection;
    int qte;
    QList<Composant> listComposant;//liste de tous les composants du produit.
    QList<Composant> listComposantAffaire;//liste de tous les composants achetés sur affaire du produit.
    QList<Composant> listComposantFG;//liste de tous les composants FG du produit.
    QList<Section> listSection;//Liste de toutes les sections du produit.
    QList<Composant> baseCommuneComposants;//liste de tous les composants de la base commune.
    QList<Operation> baseCommuneOperations;//liste de tous les composants de la base commune.
    QList<Operation> listOperation;//liste de toutes les opérations du produit.
    QList<QString> codeProduit;//liste de tous les codes produits du produit
    double prixTotNomAffaire;//prix de revient total de la Nomenclature marché.
    double prixTotNomFG;//prix de revient total de la Nomenclature FG.
    double prixTotMdo;
    double prixVenteMarche;
    double nbHCdp;//nombre d'heure cdp
    double nbHTech;
    double nbHOuv;
    QList<RegleCode> listRegle;//Liste de toutes les régles du produit.
    QList<Marche> listMarche;//liste de tous les marchés du produit.
    QList<Codet> listCodet;//liste des codets du produit actuel

};

#endif // PRODUIT_H
