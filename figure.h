#ifndef FIGURE_H
#define FIGURE_H

#include "pix.h"

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class figure : public QObject
{
    Q_OBJECT
public:
    explicit figure(QGraphicsScene *scene,int type, QObject *parent = nullptr,bool stoped=false);
    int pixspos[4];
    pix* pixs[4];
    bool isBlueUnder(pix* p);
    bool isBlue(pix* p,int dx, int dy);
    void recolor();
    void removeFromScene();
    void move(int dx, int dy);
    bool canMove(int dx, int dy);
    void rotate();
    bool rotatable();
public slots:
    void fall();
signals:
    void stoped();
private:
    QGraphicsScene *m_scene;

};

#endif // FIGURE_H
