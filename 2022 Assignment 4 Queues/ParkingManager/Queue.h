/**
 * An implementation of Stack structure based on class template.
 *
 * Author: AzurIce(XiaoBin)
 * Date: 2022-10-13
 *
 **/

#ifndef QUEUE_H
#define QUEUE_H

#define DEFAULT_CAP 256

#include <QString>
#include <QDebug>
#include <cstdlib>

template <typename T>
class Queue {
public:
    Queue();
    Queue(int _capacity);
    ~Queue();

    void push(T val);
    T front();
    T pop_front();
    T pop_tail();
    T pop();
    void clear();

    int size();
    bool empty();

    QString toString();
private:
    int _front;
    int _rear;  // After the last element
    int _capacity;
    T* _queue;

    void reArrange();

    bool resize(int capacity);

    int indexAdd(int i, int x) {
        return (i + x) % _capacity;
    }
    int indexSub(int i, int x) {
        return i - x < 0 ? i - x + _capacity : i - x;
    }
};

// Construtors and Deconstructor
template <typename T>
Queue<T>::Queue(): _capacity(DEFAULT_CAP), _front(0), _rear(0) {
    _queue = (T*) malloc(sizeof(T) * DEFAULT_CAP);
    if (!_queue) { // Error
//        qDebug() << "Stack Construction Error";
    }
}

template <typename T>
Queue<T>::Queue(int _capacity): _capacity(_capacity), _front(0), _rear(0) {
    _queue = (T*) malloc(sizeof(T) * _capacity);
    if (!_queue) { // Error
//        qDebug() << "Stack Construction Error";
    }
}

template <typename T>
Queue<T>::~Queue() {
    free(_queue);
    _queue = nullptr;
}

template <typename T>
void Queue<T>::reArrange() {
    T* tmpQueue = (T*) malloc(sizeof(T) * _capacity);
    memcpy(tmpQueue, _queue, _capacity);
    if (_rear > _front) {
        memcpy(_queue, tmpQueue + _front, _rear - _front);
    } else if (_rear < _front) {
        memcpy(_queue, tmpQueue + _front, _capacity - _front);
        memcpy(_queue + _capacity - _front, tmpQueue + _rear, _front - _rear);
    }
    free(tmpQueue);
    _front = 0;
    _rear = _capacity - 1;
}

template <typename T>
bool Queue<T>::resize(int capacity) {
    reArrange();

    T* newQueue = (T*) realloc(_queue, sizeof(T) * capacity);
    if (newQueue) {
        _capacity = capacity;
        _queue = newQueue;
        return true;
    }
    return false;
}


// Basic operation of Stack
template <typename T>
void Queue<T>::push(T val) {
    bool f = true;
    if (size() + 1 == _capacity) {
        f = resize(_capacity * 2);
    }
    if (!f) return; // Error
    _queue[_rear] = val;
    _rear = indexAdd(_rear, 1);
}

template <typename T>
T Queue<T>::front() {
    T emptyElem;
    if (!size()) return emptyElem;
    return _queue[_front];
}

template <typename T>
T Queue<T>::pop_front() {
    T emptyElem;
    if (!size()) return emptyElem;
    _front = indexAdd(_front, 1);
    return _queue[indexSub(_front, 1)];
}
template <typename T>
T Queue<T>::pop_tail() {
    T emptyElem;
    if (!size()) return emptyElem;
    _rear = indexSub(_rear, 1);
    return _queue[_rear];
}
template <typename T>
T Queue<T>::pop() {
    return pop_front();
}
template <typename T>
void Queue<T>::clear() {
    while (size()) pop_tail();
}

template <typename T>
int Queue<T>::size() {
    return _rear < _front ? _capacity - _front + _rear : _rear - _front;
}

template <typename T>
bool Queue<T>::empty() {
    return size() == 0;
}

template <typename T>
QString Queue<T>::toString() {
    QString s = "[";
    for (int i = _front; i != _rear; i = indexAdd(i, 1)) {
        s.append(_queue[i]);
        if (indexAdd(i, 1) != _rear) s.append(", ");
    }
    s.append("]");
    return s;
}

template<>
QString Queue<double>::toString();
template<>
QString Queue<int>::toString();

#endif // QUEUE_H
