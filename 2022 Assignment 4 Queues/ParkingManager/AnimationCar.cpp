#include "AnimationCar.h"

#include <QPainterPath>
AnimationCar::AnimationCar(QObject *target, QObject *parent, int n, int source, int dest):
    QPropertyAnimation (target, "pos", parent), n(n), source(source), dest(dest) {
    if (dest == 0) return;

    int w = 2 * ceil(sqrt(n * 0.5));
    int h = (n + w - 1) / w;
//    qDebug() << "w: " << w << ", h: "<< h;


    qDebug() << "source: " << source << ", dest: " << dest;
    if (source == 0) {
        qDebug() << "inAnim";
        path.clear();
        int x = -5 - 5, y = -10 - 5;
        path.moveTo(x, y);
        x = -5 - 5; y = 10 + 5; path.lineTo(x, y);
        x += 10; path.lineTo(x, y);
        int id = 1;

        int l = 0, r = (w - 1) * 10;
        qDebug() << r;
        for (int i = 1; i <= h;) {
            int dir = x == r ? -1 : 1;

            for (int j = 1; j < w && id != dest && id + w != dest; j++) {
                id += dir;
                x += dir * (10);
            }
            if (id == dest || id + w == dest) {
                path.lineTo(x, y);
                y += (id == dest ? -1 : 1) * (5 + 10);
                path.lineTo(x, y);
                return;
            }
            x += dir * 10;
            path.lineTo(x, y);
            if (h - i >= 2) {
                y += 40 + 10;
                i += 2;
                path.lineTo(x, y);
            } else {
                y += 20 + 10;
                path.lineTo(x, y);
                break;
            }
            x -= dir * 10;
            id += 2*w;
        }
    } else /*if (dest == n + 1)*/ {
        qDebug() << "outAnim";
        int i = source % w;
        int j = (source + w - 1) / w;
        qDebug() << "i: " << i << ", j: " << j;
        path.clear();
        int x = (i-1) * 10;
        int y = (j-1) * 20 + j / 2 * 10;
        qDebug() << "x: " << x << ", y: " << y;
        path.moveTo(x, y);

        if (j % 2) {
            y += 10 + 5;
        } else {
            y -= 10 + 5;
        }
        path.lineTo(x, y);

        int l = 0, r = (w - 1) * 10;
        qDebug() << "l: " << l << ", r: " << r;
        int dir = (j + 1) / 2 % 2 ? 1 : -1;
        qDebug() << "dir: " << dir;

        if ((dir == 1 || x != l) && (dir == -1 || x != r)) {
            do {
                x += dir * (10);
                qDebug() << x;
            } while (x != l && x != r);
            path.lineTo(x, y);
        }
        x += dir * 10;
        path.lineTo(x, y);
        if (h - j >= 2) {
            y += 40 + 10;
            j += 2;
            path.lineTo(x, y);
        } else {
            y += 20 + 10;
            path.lineTo(x, y);
            return;
        }
        x -= dir * 10;

        for (; j <= h;) {
            if (x == r) { x = l; dir = -1;}
            else { x = r; dir = 1;}
            path.lineTo(x, y);

            x += dir * 10;
            path.lineTo(x, y);
            if (h - j >= 2) {
                y += 40 + 10;
                j += 2;
                path.lineTo(x, y);
            } else {
                y += 20 + 10;
                path.lineTo(x, y);
                break;
            }
            x -= dir * 10;
        }
    }
}


void AnimationCar::updateCurrentTime(int currentTime)
{
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
}
