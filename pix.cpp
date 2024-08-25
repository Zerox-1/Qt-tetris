#include "pix.h"

pix::pix(int i)
{
    setRect(0, 0, 30, 30); // Размер квадрата 30x30 пикселей
    if (i == 0) {
        setBrush(Qt::lightGray);
    } else if(i==1) {
        setBrush(Qt::red);
    }
    else{
        setBrush(Qt::blue);
    }
}

void pix::recolor()
{
    setBrush(Qt::blue);
}

void pix::setMyPos(int x, int y)
{
    setPos(x * 30, y * 30);
}
