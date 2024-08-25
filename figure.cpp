#include "figure.h"
#include "mainwindow.h"
#include <algorithm>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>

extern MainWindow *w;

int figures[7][4] = {
    {1, 3, 5, 7},
    {2, 3, 4, 5},
    {1, 2, 3, 5},
    {1, 2, 3, 4},
    {0, 2, 3, 4},
    {1, 0, 2, 4},
    {0, 1, 3, 5}
};

figure::figure(QGraphicsScene *scene,int type, QObject *parent,bool stoped) : QObject(parent), m_scene(scene)
{
    if(!stoped){
        std::copy(std::begin(figures[type]), std::end(figures[type]), pixspos);
        for (int i = 0; i < 4; i++) {
            pixs[i] = new pix(1);
            m_scene->addItem(pixs[i]); // Use m_scene instead of parent->scene
            if (pixspos[i] % 2 == 0) {
                pixs[i]->setMyPos(0, pixspos[i] / 2);
            } else {
                pixs[i]->setMyPos(1, (pixspos[i] - 1) / 2);
            }
        }
    }
    else{
        std::copy(std::begin(figures[type]), std::end(figures[type]), pixspos);
        for (int i = 0; i < 4; i++) {
            pixs[i] = new pix(1);
            m_scene->addItem(pixs[i]); // Use m_scene instead of parent->scene
            if (pixspos[i] % 2 == 0) {
                pixs[i]->setMyPos(12, pixspos[i] / 2+2);
            } else {
                pixs[i]->setMyPos(13, (pixspos[i] - 1) / 2+2);
            }
        }
    }
}

bool figure::isBlueUnder(pix* p) {
    QList<QGraphicsItem*> items = m_scene->items(QPointF(p->x()+1, p->y() + 30));
    for (QGraphicsItem* item : items) {
        pix* px = dynamic_cast<pix*>(item);
        if (px && px->brush().color() == Qt::blue) {
            return true;
        }
    }
    return false;
}

bool figure::isBlue(pix *p, int dx, int dy)
{
    QList<QGraphicsItem*> items = m_scene->items(QPointF(p->x()+dx, p->y() + dy));
    for (QGraphicsItem* item : items) {
        pix* px = dynamic_cast<pix*>(item);
        if (px && px->brush().color() == Qt::blue) {
            return true;
        }
    }
    return false;
}


void figure::recolor()
{
    for (int i = 0; i < 4; i++) {
            QList<QGraphicsItem*> items = m_scene->items(QPointF(pixs[i]->x()+1, pixs[i]->y()+1));
            for (QGraphicsItem* item : items) {
                pix* px = dynamic_cast<pix*>(item);
                if (px && px != pixs[i]) {
                    px->setBrush(Qt::blue);
                }
            }
        }
}

void figure::removeFromScene()
{
    for(int i = 0; i < 4; i++) {
            m_scene->removeItem(pixs[i]);
            delete pixs[i];
    }
}

void figure::move(int dx, int dy)
{
    if (canMove(dx, dy)) {
        for (int i = 0; i < 4; i++) {
            pixs[i]->setPos(pixs[i]->x() + dx, pixs[i]->y() + dy);
        }
        m_scene->update();
    }
}

bool figure::canMove(int dx, int dy)
{
    for(int i = 0; i < 4; ++i) {
        if(isBlue(pixs[i],dx,dy)) {
            return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        qreal newX = pixs[i]->x() + dx;
        qreal newY = pixs[i]->y() + dy;
        if (newX < 0 || newX >= 300 || newY >= 600) {
            return false;
        }
//        QList<QGraphicsItem*> items = m_scene->items(QPointF(newX, newY));
//        for (QGraphicsItem* item : items) {
//            if (item != pixs[i] && dynamic_cast<pix*>(item)) {
//                return false;
//            }
//        }
    }
    return true;
}

void figure::rotate() {
    if(rotatable()){
        int centerX = pixs[1]->x();
        int centerY = pixs[1]->y();

        for (int i = 0; i < 4; ++i) {
            int oldX = pixs[i]->x();
            int oldY = pixs[i]->y();
            int newX = centerX + centerY - oldY;
            int newY = centerY - centerX + oldX;
            pixs[i]->setPos(newX, newY);
        }
        m_scene->update();
    }
}

bool figure::rotatable()
{
    int centerX = pixs[1]->x();
    int centerY = pixs[1]->y();
    for (int i = 0; i < 4; ++i) {
            int oldX = pixs[i]->x();
            int oldY = pixs[i]->y();
            int newX = centerX + centerY - oldY;
            int newY = centerY - centerX + oldX;

            // Проверка на выход за границы поля
            if (newX < 0 || newX >= 300 || newY >= 600 || newY < 0) {
                return false;
            }
        }
        return true;
}

void figure::fall()
{
    for(int i = 0; i < 4; ++i) {
        if(isBlueUnder(pixs[i])) {
            recolor();
            emit stoped();
            return;
        }
    }

    if(pixs[3]->y() != 600 - 30) {
            for(int i = 0; i < 4; i++) {
                pixs[i]->setPos(pixs[i]->x(), pixs[i]->y() + 30);
            }
            m_scene->update();
    }
    else {
        recolor();
        emit stoped();
    }
}
