#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pix.h"
#include "figure.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsView>
#include <qtimer.h>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), score(new Score()), timer(new QTimer())
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            pixel1 = new pix();
            scene->addItem(pixel1);
            pixel1->setMyPos(j, i);
        }
    }
    randomType = qrand() % 7;
    QGraphicsView* view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setParent(ui->groupBox);
    view->setGeometry(0, 0, ui->groupBox->width(), ui->groupBox->height());
    view->show();
    view->setFixedSize(800, 800);
    scene->setSceneRect(0, 0, 800, 800);
    scene->addItem(score);
    fig = new figure(scene,randomType, this);
    randomType = qrand() % 7;
    nextfig=new figure(scene,randomType, this,true);
    connect(timer, SIGNAL(timeout()), fig, SLOT(fall()));
    connect(fig, &figure::stoped, this, &MainWindow::check);
    TimerStart();

    this->setFocus();
    this->setFocusPolicy(Qt::StrongFocus);
}
void MainWindow::TimerStart()
{
    timer->start(300);
}

void MainWindow::createNew()
{
    if (fig) {
        fig->removeFromScene();
        delete fig;
    }
    fig = new figure(scene,randomType, this);
    randomType = qrand() % 7;
    nextfig->removeFromScene();
    nextfig=new figure(scene,randomType, this,true);
    connect(timer, SIGNAL(timeout()), fig, SLOT(fall()));
    connect(fig, &figure::stoped, this, &MainWindow::check);
    TimerStart();
}

void MainWindow::check()
{
    int mnozhitel=0;
    for (int i=20;i>0;i--) {
        for (int j=0;j<10;j++) {
            QList<QGraphicsItem*> items = scene->items(QPointF(j*30+1, i*30+1));
            bool teemp=true;
            for (QGraphicsItem* item : items) {
                pix* px = dynamic_cast<pix*>(item);
                if (px && px->brush().color() == Qt::lightGray) {
                    teemp=false;
                    break;
                }
                else if (px && px->brush().color() == Qt::blue and j==9) {
                    deleteLine(i);
                    mnozhitel++;
                    i++;
                }
            }
            if(!teemp){
                break;
            }
        }
    }
    score->increase(mnozhitel);
    QList<QGraphicsItem*> items = scene->items(QPointF(60, 90));
    bool teemp=true;
    for (QGraphicsItem* item : items) {
        pix* px = dynamic_cast<pix*>(item);
        if (px && px->brush().color() == Qt::blue) {
            teemp=false;
            break;
        }
    }
    if(teemp){
        createNew();
    }
    else{
        endGame();
    }
}

void MainWindow::onMessageBoxClosed()
{
    this->close();
}

void MainWindow::deleteLine(int y)
{
    for (int i = 0; i < 10; i++) {
        QList<QGraphicsItem*> items = scene->items(QPointF(i*30+1, y*30+1));
        for (QGraphicsItem* item : items) {
            pix* px = dynamic_cast<pix*>(item);
            if (px) {
                if (px->scene() == scene) {
                    scene->removeItem(px);
                    px->deleteLater();
                }
            }
        }
    }

    for (int row = y - 1; row >=0; --row) {
        for (int col = 0; col < 10; ++col) {
            QList<QGraphicsItem*> items = scene->items(QPointF(col*30+1, row*30+1));
            for (QGraphicsItem* item : items) {
                pix* px = dynamic_cast<pix*>(item);
                if (px) {
                    if (px->scene() == scene) {
                        px->setMyPos(col, row + 1);
                    }
                }
            }
        }
    }
        for (int j = 0; j < 10; j++) {
            pixel1 = new pix();
            scene->addItem(pixel1);
            pixel1->setMyPos(j, 0);
        }
        scene->update();
}

void MainWindow::endGame()
{
    timer->stop();
    fig->removeFromScene();
    delete fig;
    nextfig->removeFromScene();
    delete nextfig;
    QMessageBox* messageBox = new QMessageBox(this);
        messageBox->setModal(true);
        messageBox->setFont(QFont("times", 16));
        messageBox->setWindowTitle("Game Over");
        messageBox->setText("Score: " + QString::number(score->getScore()));
        messageBox->setStandardButtons(QMessageBox::Ok);
        connect(messageBox, &QMessageBox::finished, this, &MainWindow::onMessageBoxClosed);

        messageBox->show();
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        fig->move(-30, 0);
        break;
    case Qt::Key_Right:
        fig->move(30, 0);
        break;
    case Qt::Key_Down:
        fig->move(0, 30);
        break;
    case Qt::Key_Up:
        fig->rotate();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

