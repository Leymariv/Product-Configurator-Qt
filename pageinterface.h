#ifndef PAGEINTERFACE_H
#define PAGEINTERFACE_H

#include <QtPlugin>
#include <QWidget>
#include <iostream>
#include <string>


class PageInterface
{
    public:
    PageInterface(QWidget* parent, int iC, int iP);
    PageInterface(QWidget* parent);
    virtual void goNext();
    virtual void signalAndSlot();
    virtual void setCourPrec(int c, int p );

    protected:
        int indexCourant;
        int indexPrecedant;

    private:
        QWidget* p;
};

Q_DECLARE_INTERFACE(PageInterface, "Configurator.Interface/1.0")

#endif 
