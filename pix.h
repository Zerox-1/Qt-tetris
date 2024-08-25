#ifndef PIX_H
#define PIX_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsRectItem>
#include <QWidget>

class pix:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    pix(int i=0);
    void recolor();
    void setMyPos(int x,int y);
};

#endif // PIX_H
