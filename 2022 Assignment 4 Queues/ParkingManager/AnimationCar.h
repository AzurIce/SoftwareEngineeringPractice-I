#ifndef ANIMATIONCAR_H
#define ANIMATIONCAR_H

#include <QPropertyAnimation>
#include <QPainterPath>

class AnimationCar : public QPropertyAnimation
{
public:
    AnimationCar(QObject *target, QObject *parent, int total, int source, int dest);
private:
    int n;
    int source;
    int dest;
    QPainterPath path;
    void updateCurrentTime(int currentTime);
};

#endif // ANIMATIONCAR_H
