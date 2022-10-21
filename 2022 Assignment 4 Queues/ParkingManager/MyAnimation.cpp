#include "MyAnimation.h"
#include <QPainterPath>

MyAnimation::MyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent):
    QPropertyAnimation (target, propertyName, parent),
    arcPath(false) {

}

void MyAnimation::setArcPath(bool isTrue) {
    arcPath = isTrue;
}

void MyAnimation::updateCurrentTime(int currentTime)
{
    QPainterPath path = QPainterPath();
    if (arcPath) {
        if (path.isEmpty()) {
            QPointF to = endValue().toPointF();
            QPointF from = startValue().toPointF();
            path.moveTo(from);
            qreal tempWidth = from.rx() - to.rx();
            qreal tempHeight = from.ry() - to.ry();
            QRectF tempRect = QRectF(to.x() - tempWidth, to.y(), tempWidth*2, tempHeight*2);
            path.arcTo(tempRect, 0, 90);
        }
        int dura = duration();
        const qreal progress = ((dura == 0) ? 1 : ((((currentTime - 1) % dura) + 1) / qreal(dura)));

        qreal easedProgress = easingCurve().valueForProgress(progress);
        if (easedProgress > 1.0) {
            easedProgress -= 1.0;
        } else if (easedProgress < 0) {
            easedProgress += 1.0;
        }
        QPointF pt = path.pointAtPercent(easedProgress);
        updateCurrentValue(pt);
        emit valueChanged(pt);
    } else {
        QPropertyAnimation::updateCurrentTime(currentTime);
    }
}
