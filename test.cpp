

#include "test.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlerror.h>

#include <qapplication>
#include <QSettings>
#include <QtSql/qsqldatabase.h>
#include "pathConfig.h"

FenPrinc::FenPrinc(QWidget *parent) : PageInterface(parent)
{

QString s  = "5.3";
int v = s.toDouble();
    qDebug()<< v;

}
