#ifndef STACK_H
#define STACK_H

#include <QDebug>
#include <QString>
#include <iostream>

#define DEFAULT_CAP 256

template <typename T>
class Stack
{
public:
    Stack(): _capacity(DEFAULT_CAP), _size(0) {
        qDebug() << "Stack Contructor";
        _stack = (T*) malloc(sizeof(T) * DEFAULT_CAP);
        if (!_stack) { // Error
            qDebug() << "Stack Construction Error";
        }
    }
    Stack(int _capacity): _capacity(_capacity), _size(0) {
        qDebug() << "Stack Contructor";
        _stack = (T*) malloc(sizeof(T) * _capacity);
        if (!_stack) { // Error
            qDebug() << "Stack Construction Error";
        }
    }
    ~Stack() {
        free(_stack);
        _stack = nullptr;
    }

    void push(T val) {
        bool f = true;
        if (_size + 1 == _capacity) {
            f = resize(_capacity * 2);
        }
        if (!f) return; // Error
        _stack[_size++] = val;
    }
    T top() {
        T emptyElem;
        if (!_size) return emptyElem;
        return _stack[_size - 1];
    }
    T pop() {
        T emptyElem;
        if (!_size) return emptyElem;
        _size--;
        return _stack[_size];
    }

    int size() {
        return _size;
    }
    bool empty() {
        return _size == 0;
    }
    void clear() {
        while (_size) pop();
    }
    QString toString() {
        QString s = "[";
        for (int i = 0; i < _size; i++) {
            s.append(_stack[i]);
            if (i != _size - 1) s.append(", ");
        }
        return s;
    }
private:
    int _capacity;
    int _size;
    T* _stack;

    bool resize(int _capacity) {
        T* newStack;
        newStack = (T*) realloc(_stack, sizeof(T) * _capacity);
        if (newStack) {
            this->_capacity = _capacity;
            _stack = newStack;
            return true;
        }
        return false;
    }
};

template <>
class Stack<double>
{
public:
    Stack(): _capacity(DEFAULT_CAP), _size(0) {
        qDebug() << "Stack Contructor";
        _stack = (double*) malloc(sizeof(double) * DEFAULT_CAP);
        if (!_stack) { // Error
            qDebug() << "Stack Construction Error";
        }
    }
    Stack(int _capacity): _capacity(_capacity), _size(0) {
        qDebug() << "Stack Contructor";
        _stack = (double*) malloc(sizeof(double) * _capacity);
        if (!_stack) { // Error
            qDebug() << "Stack Construction Error";
        }
    }
    ~Stack() {
        free(_stack);
        _stack = nullptr;
    }

    void push(double val) {
        bool f = true;
        if (_size + 1 == _capacity) {
            f = resize(_capacity * 2);
        }
        if (!f) return; // Error
        _stack[_size++] = val;
    }
    double top() {
        double emptyElem;
        if (!_size) return emptyElem;
        return _stack[_size - 1];
    }
    double pop() {
        double emptyElem;
        if (!_size) return emptyElem;
        _size--;
        return _stack[_size];
    }

    int size() {
        return _size;
    }
    bool empty() {
        return _size == 0;
    }
    void clear() {
        while (_size) pop();
    }
    QString toString() {
        QString s = "[";
        for (int i = 0; i < _size; i++) {
            s.append(QString::number(_stack[i]));
            if (i != _size - 1) s.append(", ");
        }
        return s;
    }
private:
    int _capacity;
    int _size;
    double* _stack;

    bool resize(int _capacity) {
        double* newStack;
        newStack = (double*) realloc(_stack, sizeof(double) * _capacity);
        if (newStack) {
            this->_capacity = _capacity;
            _stack = newStack;
            return true;
        }
        return false;
    }
};
#endif // STACK_H
