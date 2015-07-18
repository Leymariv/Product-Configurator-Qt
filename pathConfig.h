#include <QApplication>

#ifndef PATHCONFIG_H
#define PATHCONFIG_H

#ifdef QT_DEBUG
    #define INIFILECONTAINER     ("PathsDebug")
    #define PATHMAINDOSSIER      ("/../../ProductConfigurator/")
#else
    #define INIFILECONTAINER     ("PathsRelease")
    #define PATHMAINDOSSIER      ("/")

#endif

#endif // PATHCONFIG_H
