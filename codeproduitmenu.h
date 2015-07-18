#ifndef CODEPRODUITMENU_H
#define CODEPRODUITMENU_H

#include <QWidget>
#include "pageinterface.h"
#include "produit.h"

namespace Ui {
class CodeProduitMenu;
}

class CodeProduitMenu : public QWidget, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

signals:
    void changeIndex(int);

public slots:
  void goPrec();
  void goMainMenu();


public:
    explicit CodeProduitMenu(QWidget *parent = 0,
                             int iC = 0, int iP = 0, Produit *p = 0);


  void afficheCode();//set a afficher le code produit depuis windows
  void setProduit(Produit*p){this->currentProduit = p;}//sert a set le current produit depuis windows

    ~CodeProduitMenu();

private:
    void signalAndSlot();
    Ui::CodeProduitMenu *ui;
    Produit *currentProduit;
};

#endif // CODEPRODUITMENU_H
