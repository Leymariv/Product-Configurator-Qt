#include "saisicode.h"
#include "ui_saisicode.h"

SaisiCode::SaisiCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaisiCode)
{
    ui->setupUi(this);
}

SaisiCode::~SaisiCode()
{
    delete ui;
}
