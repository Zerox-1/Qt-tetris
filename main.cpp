#include <QApplication>
#include "mainwindow.h"

MainWindow *w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow; // Инициализация глобального указателя
    w->show();
    return a.exec();
}
