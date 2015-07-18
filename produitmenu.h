#ifndef PRODUITMENU_H
#define PRODUITMENU_H

#include <QWidget>
#include <QDialog>
#include <QPalette>
#include <QFile>
#include <QDesktopServices>
#include <QMessageBox>
#include <QApplication>
#include <QString>
#include <QUrl>

#include "pageinterface.h"
#include "windows.h"
#include "produit.h"
#include "mainmenusection.h"

namespace Ui {
class ProduitMenu;
}

class ProduitMenu : public QWidget,public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

signals:
    void changeIndex(int);
    void mainSectionMenu(Produit *p);

public slots:
  void goPrec();
  void openImage();
  void openPDF();
  void goMainSectionMenu();

public:
    explicit ProduitMenu(QWidget *parent = 0,
                         int iC = 0, int iP = 0, QString name = 0);

    ~ProduitMenu();

private:
    Ui::ProduitMenu *ui;
    void signalAndSlot();
    Produit findProduit(QString nProduit); //retourne le produit dont le nom est passé en paramétre

    QString produitName;
    QString path;
    Produit p;

};

#endif // PRODUITMENU_H
