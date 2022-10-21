#ifndef MYANIMATION_H
#define MYANIMATION_H

#include <QPropertyAnimation>

class MyAnimation : public QPropertyAnimation
{
public:
    MyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent);
    void setArcPath(bool isTrue);
private:
    void updateCurrentTime(int currentTime);
    bool arcPath;
};

#endif // MYANIMATION_H
