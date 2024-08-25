#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Score.h"
#include "figure.h"
#include "pix.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void TimerStart();

protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Score *score;
    pix *pixel1;
    figure * fig;
    figure * nextfig;
    QTimer *timer;
    int randomType;
    void deleteLine(int y);
    void endGame();
public slots:
    void createNew();
    void check();
    void onMessageBoxClosed();
signals:
    void sceneInitialized(QGraphicsScene *scene);
};

#endif // MAINWINDOW_H
