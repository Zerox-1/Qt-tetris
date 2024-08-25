#include "Score.h"

#include <QFont>

Score::Score(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    score=0;
    setX(600);
    setPlainText("Score: "+QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
}

void Score::increase(int y)
{
    score+=y;
    setPlainText("Score: "+QString::number(score));
}

int Score::getScore()
{
    return score;
}

void Score::setScore(int a){
    score=a;
    setPlainText("Score: "+QString::number(score));
}
