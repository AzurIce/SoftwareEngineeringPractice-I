#include "queue.h"

template<>
QString Queue<double>::toString() {
    QString s = "[";
    for (int i = _front; i != _rear; i = indexAdd(i, 1)) {
        s.append(QString::number(_queue[i]));
        if (indexAdd(i, 1) != _rear) s.append(", ");
    }
    s.append("]");
    return s;
}
template<>
QString Queue<int>::toString()  {
    QString s = "[";
    for (int i = _front; i != _rear; i = indexAdd(i, 1)) {
        s.append(QString::number(_queue[i]));
        if (indexAdd(i, 1) != _rear) s.append(", ");
    }
    s.append("]");
    return s;
}
