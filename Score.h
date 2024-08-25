#ifndef SCORE_H
#define SCORE_H

#include <qgraphicsitem.h>



class Score: public QGraphicsTextItem
{
public:
    Score(QGraphicsItem * parent=0);
    void increase(int y);
    int getScore();
    void setScore(int a);
private:
    int score;
};


#endif // SCORE_H
