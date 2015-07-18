#ifndef TEST_H
#define TEST_H


#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QDateEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <QStackedWidget>
#include <QPlainTextEdit>
#include "pageinterface.h"
#include <iostream>
#include <mainmenusection.h>


#include "section.h"
#include "sectiongenerique.h"
#include "composant.h"
#include "composantfg.h"
#include "composantaffaire.h"

class FenPrinc : public QWidget, public PageInterface
{
    Q_OBJECT
    Q_INTERFACES(PageInterface)

    public:
    FenPrinc(QWidget *parent=0);

};


#endif // TEST_H
