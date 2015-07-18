#ifndef PRODUITLISTE_H
#define PRODUITLISTE_H

#include <QWidget>

#include "pageinterface.h"
#include "mainmenusection.h"
#include "windows.h"
#include "data.h"
#include "produit.h"

namespace Ui {
class ProduitListe;
}

class ProduitListe : public QWidget, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

signals:
    void changeIndex(int);
    void goProduitMenu(QString);

public slots:
  void callProduitMenu(QString s);
  void goPrec();
  void eraseTab();

public:
    explicit ProduitListe(QWidget *parent = 0,
                          int iC=0, int iP=0);
    ~ProduitListe();

private:
    Ui::ProduitListe *ui;
    void signalAndSlot();

};

#endif // PRODUITLISTE_H
