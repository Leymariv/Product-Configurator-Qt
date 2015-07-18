#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T10:56:11
#
#-------------------------------------------------

QT       += core gui \
            widgets \
            xml \
            core


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProductConfigurator
TEMPLATE = app

RC_FILE = myapp.rc


QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder


SOURCES += \
    main.cpp \
    login.cpp \
    marcheliste.cpp \
    produitliste.cpp \
    pageinterface.cpp \
    windows.cpp \
    commentaire.cpp \
    mainmenusection.cpp \
    produitmenu.cpp \
    data.cpp \
    produit.cpp \
    section.cpp \
    listderoul.cpp \
    optcocher.cpp \
    sectiongenerique.cpp \
    infochamp.cpp \
    composant.cpp \
    composantfg.cpp \
    test.cpp \
    composantaffaire.cpp \
    code.cpp \
    codeproduitmenu.cpp \
    resumeconfiguration.cpp \
    reglecode.cpp \
    marche.cpp \
    codet.cpp \
    frais.cpp \
    mdo.cpp \
    operation.cpp


HEADERS += \
    login.h \
    marcheliste.h \
    produitliste.h \
    pageinterface.h \
    test.h \
    windows.h \
    commentaire.h \
    mainmenusection.h \
    produitmenu.h \
    data.h \
    produit.h \
    section.h \
    listderoul.h \
    optcocher.h \
    sectiongenerique.h \
    infochamp.h \
    composant.h \
    composantfg.h \
    composantaffaire.h \
    code.h \
    codeproduitmenu.h \
    resumeconfiguration.h \
    reglecode.h \
    marche.h \
    codet.h \
    frais.h \
    mdo.h \
    operation.h \
    pathConfig.h

RESOURCES += \
    img.qrc

FORMS += \
    login.ui \
    produitliste.ui \
    Windows.ui \
    marcheliste.ui \
    commentaire.ui \
    mainmenusection.ui \
    produitmenu.ui \
    sectiongenerique.ui \
    codeproduitmenu.ui \
    resumeconfiguration.ui
