#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <windows.h>


#include "pageinterface.h"


namespace Ui {
class Login;
}

class Login : public QDialog, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

public slots:
    void checkLogin();

signals:
    void changeIndex(int);

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;
    void signalAndSlot();
    void goNext();
};

#endif // LOGIN_H
