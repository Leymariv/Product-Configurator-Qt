#include "commentaire.h"
#include "ui_commentaire.h"

Commentaire::Commentaire(QWidget *parent,
                         int iC, int iP,
                         Produit *produit,
                         Data *d) :
    QWidget(parent),
    ui(new Ui::Commentaire),
    PageInterface(parent, iC, iP)
{
    ui->setupUi(this);
    currentProduit = produit;
    database = d;
    signalAndSlot();

    //on doit remplacer dans ce path les "/" par des "\" => "\\" caractére d'échapement
    //c'est qt qui les mets dans ce sens avec la méthode appicationDirPath()
    pathSyst = updatePath(QApplication::applicationDirPath()+database->getPathSyst());
    pathBA = updatePath(QApplication::applicationDirPath()+database->getPathBA());
}

QString Commentaire::updatePath(QString path){
    QString result = path;
    for(int i=0 ; i <result.size();i++){//on doit remplacer dans ce path les "/" par des "\" => "\\" caractére d'échapement
        if(result.at(i) == '/'){//c'est qt qui les mets dans ce sens avec la méthode appicationDirPath()
            result.replace(i,1,"\\");
        }
    }
    return result;
}


void Commentaire::signalAndSlot(){
    QObject::connect(ui->precBouton, SIGNAL(clicked()), this, SLOT(goPrec()));
    QObject::connect(ui->suivBouton,SIGNAL(clicked()),this,SLOT(goNext()));//on déclenche le thread lors du click sur le bouton pour générer les fichiers
    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));
    QObject::connect(this,SIGNAL(changeIndex(int)), this->parent(),
                     SLOT(changeIndex(int)));

}

void Commentaire::goPrec(){
    emit changeIndex(this->indexPrecedant);
}

void Commentaire::goNext(){

    QString qteString =  ui->qteEdit->text();

    QRegExp rx("[1-9]\\d{0,3}");
    QValidator *validator = new QRegExpValidator(rx, 0);
    int pos = 0;
    if(validator->validate(qteString,pos) != 2){
        QMessageBox::warning(this,"Erreur de saisie","Veuillez saisir un nombre entre 1 et 999");
        return;
    }
    else{
        currentProduit->setQte(ui->qteEdit->text().toInt());
        if(generateReplaceVBS())
            zipXlsx();
        else
            return;
    }
}

QString Commentaire::generateFillNomenclatureFG(){
    QString s = "";
    int decalage = 5;//décalage dans les excel (premiere ligne ou on va écrire, ligne 5)
    for(int i =0; i < currentProduit->getListeComposantFG().size();i++){
        Composant c = currentProduit->getListeComposantFG().value(i);
        s += "objXLWs6.Cells("+QString::number(i+decalage)+",1).Value = \""+c.getName()+"\"\n";
        s += "objXLWs6.Cells("+QString::number(i+decalage)+",2).Value = \""+c.getRef()+"\"\n" ;
        s += "objXLWs6.Cells("+QString::number(i+decalage)+",3).Value = \""+QString::number(
                    c.getQte().toInt()*currentProduit->getQte())+"\"\n" ;
        s += "objXLWs6.Cells("+QString::number(i+decalage)+",4).Value = \""+
                QString::number(c.getPrixU())+"\"\n" ;
        s += "objXLWs6.Cells("+QString::number(i+decalage)+",5).Value = \""+
                QString::number(c.getPrixU()*
                                (c.getQte().toInt())*
                                currentProduit->getQte())
                +"\"\n" ;
    }
    return s;
}

QString Commentaire::generateFillNomenclatureAffaire(){
    QString s1 = "";
    int decalage = 5;//décalage dans les excel (premiere ligne ou on va écrire, ligne 5)
    for(int i =0; i < currentProduit->getListeComposantAffaire().size();i++){
        Composant c1 = currentProduit->getListeComposantAffaire().value(i);
        s1 += "objXLWs7.Cells("+QString::number(i+decalage)+",1).Value = \""+c1.getName()+"\"\n";
        s1 += "objXLWs7.Cells("+QString::number(i+decalage)+",2).Value = \""+c1.getFournisseur()+"\"\n" ;
        s1 += "objXLWs7.Cells("+QString::number(i+decalage)+",3).Value = \""+c1.getRef()+"\"\n" ;
        s1 += "objXLWs7.Cells("+QString::number(i+decalage)+",4).Value = \""+QString::number(
                    c1.getQte().toInt()*currentProduit->getQte())+"\"\n" ;
        s1 += "objXLWs7.Cells("+QString::number(i+decalage)+",5).Value = \""+
                QString::number(c1.getPrixU())+"\"\n" ;
        s1 += "objXLWs7.Cells("+QString::number(i+decalage)+",6).Value = \""+
                QString::number(c1.getPrixU()*(c1.getQte().toInt())*
                                currentProduit->getQte())
                +"\"\n" ;
    }

    return s1;
}

QString Commentaire::generateFillBordereau(){
    QString s1 = "";
    int decalage = 5;//décalage dans les excel (premiere ligne ou on va écrire, ligne 5)
    for(int i =0; i < currentProduit->getListCodets().size();i++){
        Codet c = currentProduit->getListCodets().value(i);
        s1 += "objXLWs8.Cells("+QString::number(i+decalage)+",1).Value = \""+c.getName()+"\"\n";
        s1 += "objXLWs8.Cells("+QString::number(i+decalage)+",2).Value = \""+c.getCodeArticle()+"\"\n" ;
        s1 += "objXLWs8.Cells("+QString::number(i+decalage)+",3).Value = \""+QString::number(
                    c.getQte().toInt()*currentProduit->getQte())+"\"\n" ;
        s1 += "objXLWs8.Cells("+QString::number(i+decalage)+",4).Value = \""+
                QString::number(c.getPrixVenteU())+"\"\n" ;
        s1 += "objXLWs8.Cells("+QString::number(i+decalage)+",5).Value = \""+
                QString::number(c.getPrixVenteU()*(c.getQte().toInt())*
                                currentProduit->getQte())
                +"\"\n" ;
    }

    return s1;
}

bool Commentaire::generateReplaceVBS(){

    QString filename = pathSyst+"replace.vbs";

    cmdDos("del \""+filename+"\"");

    QFile file(filename);
    //on a besoin de caster ces valeurs pour qu'elles correspondent au excel qui ne prend pas les doubles, mais les int.

    int prixNomAff = static_cast<int>(currentProduit->getPrixTotNomAffaire());
    int prixNomFG = static_cast<int>(currentProduit->getPrixTotNomFG());
    int prixVenteMarcheCast = static_cast<int>(currentProduit->getPrixVenteMarche());
    QString prixVenteMarche = (currentProduit->getCurrentMarche().getName() == "") ? // si on a un marché, on met dans la variable le prix de vente du marché,
                                                                                     //si on ne l'a pas, on met la chaine de caractére " "
                                                                                     " ":
                                                                                     QString::number(prixVenteMarcheCast)  ;

    //Et oui! QT a besoin de doubles avec des points pour faire ses opérations, mais excel, lui a besoin de virgules! C'est magnifique!!!^ ^
    QString fraisDSS = QString::number(database->getListFrais().value(0).getPourcentage()).
            replace(".",",");
    QString fraisFin = QString::number(database->getListFrais().value(1).getPourcentage()).
            replace(".",",");
    QString fraisDir = QString::number(database->getListFrais().value(2).getPourcentage()).
            replace(".",",");
    QString fraisGen = QString::number(database->getListFrais().value(3).getPourcentage()).
            replace(".",",");


    QString coutHCdp = QString::number(database->getListMdo().value(0).getCoutH()).
            replace(".",",");
    QString coutHTech = QString::number(database->getListMdo().value(1).getCoutH()).
            replace(".",",");
    QString coutHOuv = QString::number(database->getListMdo().value(2).getCoutH()).
            replace(".",",");


    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);

        stream << "strFilename=WScript.Arguments.Item(0)\n"<<
                  "strFilename1=WScript.Arguments.Item(1)\n"<<

                  /******************SHEET2**********************/



                  "Const FromValue0 = \"nomProduit\"\n"<<
                  "Const ToValue0 = \""+currentProduit->getName()+"\"\n"<<

                  "Const FromValue = \"qteProduit\"\n"<<
                  "Const ToValue = \""+QString::number(currentProduit->getQte())+"\"\n"<<

                  "Const FromValue1 = \"mdoTech\"\n"<<

                  "Const ToValue1 = \""+QString::number(currentProduit->getNbHTech()*currentProduit->getQte())
                  .replace(".",",")+ "\"\n"<<

                  //et oui, excel ne comprends pas les "." pour les chiffres, donc on est obligé de lui passer en string...

                  "Const FromValue2 = \"mdoCdp\"\n"<<
                  "Const ToValue2 = \""+QString::number(currentProduit->getNbHCdp()*currentProduit->getQte())
                  .replace(".",",")+ "\"\n"<<

                  "Const FromValue3 = \"mdoOuv\"\n"<<
                  "Const ToValue3 = \""+QString::number(currentProduit->getNbHOuv()*currentProduit->getQte())
                  .replace(".",",")+ "\"\n"<<

                  "Const FromValue31 = \"codeProduit\"\n"<<
                  "Const ToValue31 = \""+currentProduit->getTag()+"_"
                  +currentProduit->readCode()
                  + "\"\n"<<



                  /******************SHEET3**********************/


                  "Const FromValue5 = \"fournitureAffaire\"\n"<<
                  "Const ToValue5 = "+QString::number(prixNomAff*currentProduit->getQte())+ "\n"<<

                  "Const FromValue6 = \"fournitureFG\"\n"<<
                  "Const ToValue6 = "+QString::number(prixNomFG*currentProduit->getQte())+ "\n"<<

                  "Const FromValue7 = \"prixVente\"\n"<<
                  "Const ToValue7 = \""+QString::number(prixVenteMarche.toDouble(0)
                                                        *currentProduit->getQte())+"\"\n"<<

                  /******************SHEET4**********************/


                  "Const FromValue8 = \"fraisDSS\"\n"<<
                  "Const ToValue8 = \""+fraisDSS+ "\"\n"<<

                  "Const FromValue9 = \"fraisFin\"\n"<<
                  "Const ToValue9 = \""+fraisFin+ "\"\n"<<

                  "Const FromValue10 = \"fraisDir\"\n"<<
                  "Const ToValue10 = \""+fraisDir+"\"\n"<<

                  "Const FromValue100 = \"fraisGeneraux\"\n"<<
                  "Const ToValue100 = \""+fraisGen+"\"\n"<<

                  "Const FromValue101 = \"coutHCdp\"\n"<<
                  "Const ToValue101 = \""+coutHCdp+ "\"\n"<<

                  "Const FromValue102 = \"coutHTech\"\n"<<
                  "Const ToValue102 = \""+coutHTech+ "\"\n"<<

                  "Const FromValue103 = \"coutHOuv\"\n"<<
                  "Const ToValue103 = \""+coutHOuv+"\"\n"<<

                  /******************SHEET5**********************/

                  "Const FromValue11 = \"vProd\"\n"<<
                  "Const ToValue11 = \""+currentProduit->getVersionProduitXML()+ "\"\n"<<

                  "Const FromValue12 = \"vNom\"\n"<<
                  "Const ToValue12 = \""+currentProduit->getVersionNomenclatureXML()+ "\"\n"<<

                  "Const FromValue13 = \"vOp\"\n"<<
                  "Const ToValue13 = \""+currentProduit->getVersionOperationXML()+"\"\n"<<

                  "Const FromValue14 = \"vMarch\"\n"<<
                  "Const ToValue14 = \""+currentProduit->getVersionMarcheXML()+ "\"\n"<<

                  "Const FromValue15 = \"vConf\"\n"<<
                  "Const ToValue15 = \""+database->getVersionConfXML()+"\"\n"<<

                  /******************SHEET8**********************/

                  "Const FromValue16 = \"nomMarche\"\n"<<
                  "Const ToValue16 = \""+currentProduit->getCurrentMarche().getName()+ "\"\n"<<



                  /******************REPLACE**********************/

                  "Dim objXLApp, objXLWb\n"<<
                  "Set objXLApp = CreateObject(\"Excel.Application\")\n"<<

                  "objXLApp.Visible = False\n"<<

                  "Set objXLWb = objXLApp.Workbooks.Open(strFilename)\n"<<
                  "Dim objXLWs2 : Set objXLWs2 = objXLWb.Worksheets(2)\n"<<
                  "objXLWs2.Cells.Replace FromValue0, ToValue0\n"<<
                  "objXLWs2.Cells.Replace FromValue, ToValue\n"<<
                  "objXLWs2.Cells.Replace FromValue1, ToValue1\n"<<
                  "objXLWs2.Cells.Replace FromValue2, ToValue2\n"<<
                  "objXLWs2.Cells.Replace FromValue3, ToValue3\n"<<
                  "objXLWs2.Cells.Replace FromValue31, ToValue31\n"<<

                  "Dim objXLWs3 : Set objXLWs3 = objXLWb.Worksheets(3)\n"<<
                  "objXLWs3.Cells.Replace FromValue5, ToValue5\n"<<
                  "objXLWs3.Cells.Replace FromValue6, ToValue6\n"<<
                  "objXLWs3.Cells.Replace FromValue7, ToValue7\n"<<

                  "Dim objXLWs4 : Set objXLWs4 = objXLWb.Worksheets(4)\n"<<
                  "objXLWs4.Cells.Replace FromValue8, ToValue8\n"<<
                  "objXLWs4.Cells.Replace FromValue9, ToValue9\n"<<
                  "objXLWs4.Cells.Replace FromValue10, ToValue10\n"<<
                  "objXLWs4.Cells.Replace FromValue100, ToValue100\n"<<
                  "objXLWs4.Cells.Replace FromValue101, ToValue101\n"<<
                  "objXLWs4.Cells.Replace FromValue102, ToValue102\n"<<
                  "objXLWs4.Cells.Replace FromValue103, ToValue103\n"<<

                  "Dim objXLWs5 : Set objXLWs5 = objXLWb.Worksheets(5)\n"<<
                  "objXLWs5.Cells.Replace FromValue11, ToValue11\n"<<
                  "objXLWs5.Cells.Replace FromValue12, ToValue12\n"<<
                  "objXLWs5.Cells.Replace FromValue13, ToValue13\n"<<
                  "objXLWs5.Cells.Replace FromValue14, ToValue14\n"<<
                  "objXLWs5.Cells.Replace FromValue15, ToValue15\n"<<

                  "Dim objXLWs6 : Set objXLWs6 = objXLWb.Worksheets(6)\n"<<
                  generateFillNomenclatureFG()<<

                  "Dim objXLWs7 : Set objXLWs7 = objXLWb.Worksheets(7)\n"<<
                  generateFillNomenclatureAffaire()<<

                  "Dim objXLW8 : Set objXLWs8 = objXLWb.Worksheets(8)\n"<<
                  generateFillBordereau()<<
                  "objXLWs8.Cells.Replace FromValue16, ToValue16\n"<<

                  "objXLApp.DisplayAlerts = False\n"<<
                  "objXLWb.SaveAs strFilename1, 51\n"<<
                  "objXLApp.Quit"
               << endl;
    }

    if(!file.exists()){
        QMessageBox::critical(this,"Erreur génération replace.vbs",
                              "Impossible de générer replace.vbs");
        return false;
    }
    return true;
}

void Commentaire::zipXlsx(){

    QString fileName = "";
    while(fileName == ""){//on boucle dans le cas ou l'utilisateur
        QString excelFilter = "Fichier Excel (*.xlsx)";
        //sert à récupérer le path et le nom du fichier d'ou on veut sauver l'excel généré.
        fileName = QFileDialog::getSaveFileName(this,
                                                "Choisir le nom du fichier","",
                                                excelFilter,&excelFilter);

        fileName.truncate(fileName.indexOf(".xlsx"));//on ne garde que le nom du fichier sans l'extension
        //car qt ici rajoute a la fin .xlsx, si l'utilisateur
        //entre "fichier.xlsx", on va se retrouver avec un fichier au nom "fichier.xlsx.xlsx"

        if(fileName == ""){//si l'utilisateur tente de quitter.
            int ret =  QMessageBox::warning(
                        this,"Attention","Ne pas générer les fichiers?",
                        QMessageBox::Cancel | QMessageBox::Yes);
            if(ret == QMessageBox::Yes){
                return;
            }
        }
    }
    fileName +=".xlsx";

    for(int i=0 ; i <fileName.size();i++){//on doit remplacer dans ce path les "/" par des "\" => "\\" caractére d'échapement
        if(fileName.at(i) == '/'){//c'est qt qui les mets dans ce sens avec la méthode appicationDirPath()
            fileName.replace(i,1,"\\");
        }
    }

    editFile(pathBA+"BA.xlsx",fileName);

    if(QFile::exists(fileName)){

        int ret =  QMessageBox::information(
                    this,"Excel Généré!","Votre BA a bien été généré! Voulez-vous l'ouvrir?",
                    QMessageBox::No | QMessageBox::Yes);
        if(ret == QMessageBox::Yes){
            QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
        }


        emit changeIndex(0);
    }

    else{
        QMessageBox::critical(
                    this,"Excel non Généré!",
                    "Votre BA n'a pas été généré. Consulter le fichier SYSTEM\\replace.vbs");
    }

}



void Commentaire::cmdDos(QString commande){
    system(qPrintable(commande));
}

void Commentaire::editFile(QString fileSrc, QString fileDest){
    QString vbsFile = pathSyst+"replace.vbs";
    QString cmd = "cscript";
    cmdDos(cmd+" \""+vbsFile+"\" \""+fileSrc+"\" \""+fileDest+"\"");//Litéralement: >cscript replace.vbs BA.xlsx Nomentree.xlsx
    //avec bien sur les chemins adéquat. D'ailleurs, on a besoin des guillemets pour les chemins avecs des espaces!
}



Commentaire::~Commentaire()
{
    delete ui;
}





