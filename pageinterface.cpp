#include "pageinterface.h"


    PageInterface::PageInterface(QWidget *parent, int indexC, int indexP)
    {
    indexCourant = indexC;
    indexPrecedant = indexP;
    this->p = parent;
    }

    PageInterface::PageInterface(QWidget *parent){
    this->p = parent;
    }

    void PageInterface::goNext(){
    }

    void PageInterface::signalAndSlot(){

    }

    void PageInterface::setCourPrec(int c, int p){
        indexCourant = c;
        indexPrecedant = p;
    }
