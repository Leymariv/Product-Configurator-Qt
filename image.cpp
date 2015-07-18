#include "image.h"

Image::Image(): QWidget()
{

    this->setMinimumSize(400,200);


    QPalette pal = palette();
    QImage im = QImage(":/img/Bandeau.png");

    pal.setBrush(QPalette::Window, im);
    this->setPalette( pal );



}
