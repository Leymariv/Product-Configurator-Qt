#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Login),
    PageInterface(parent)
{
    ui->setupUi(this);
    ui->passwordLine->setEchoMode(QLineEdit::Password);//asterix pour le pswd
    signalAndSlot();
}

void Login::signalAndSlot()
{
    QObject::connect(ui->anBouton, SIGNAL(clicked()), (QDialog*)this, SLOT(close()));
    QObject::connect(ui->okBouton, SIGNAL(clicked()), (QDialog*)this, SLOT(checkLogin()));
    QObject::connect((QDialog*)this,SIGNAL(changeIndex(int)),
                     ((QDialog*)this)->parent(), SLOT(changeIndex(int)));
}

void Login::checkLogin(){//comparer les informations saisies avec celles de la base de données.
    QString loginText = ui->loginLine->text();
    QString passText = ui->passwordLine->text();



        if(loginText.isEmpty() || passText.isEmpty()){
            QMessageBox::warning((QDialog*)this,"Erreur de saisi","Un des champs est vide, veuillez réessayer");
        }
        else{
    QString login = "fgsynerys";
    QString pass = "vinci2015";
    if(loginText == login && passText == pass){
        goNext();
    }
    else{
        QMessageBox::critical((QDialog*)this,"Erreur d'authentification",
                              "Combinaison incompatible, veuillez réessayer");
        ui->passwordLine->setText("");
    }
        }
    return;
}

void Login::goNext(){
    emit changeIndex(1);//on envoie le signal pour changer d'index
    ((QDialog*)this)->close();
    this->destroy(true,true);

}

Login::~Login()
{
    delete ui;
}
