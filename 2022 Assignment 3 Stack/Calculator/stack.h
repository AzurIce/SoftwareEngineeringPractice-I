/**
 * An implementation of Stack structure based on class template.
 *
 * Author: AzurIce(XiaoBin)
 * Date: 2022-09-30
 *
 **/

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
    Stack();
    Stack(int _capacity);
    ~Stack();

    void push(T val);
    T top();
    T pop();
    void clear();

    int size();
    bool empty();

    QString toString();
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

// Construtors and Deconstructor
template <typename T>
Stack<T>::Stack(): _capacity(DEFAULT_CAP), _size(0) {
    _stack = (T*) malloc(sizeof(T) * DEFAULT_CAP);
    if (!_stack) { // Error
        qDebug() << "Stack Construction Error";
    }
}

template <typename T>
Stack<T>::Stack(int _capacity): _capacity(_capacity), _size(0) {
    _stack = (T*) malloc(sizeof(T) * _capacity);
    if (!_stack) { // Error
        qDebug() << "Stack Construction Error";
    }
}

template <typename T>
Stack<T>::~Stack() {
    free(_stack);
    _stack = nullptr;
}

// Basic operation of Stack
template <typename T>
void Stack<T>::push(T val) {
    bool f = true;
    if (_size + 1 == _capacity) {
        f = resize(_capacity * 2);
    }
    if (!f) return; // Error
    _stack[_size++] = val;
}

template <typename T>
T Stack<T>::top() {
    T emptyElem;
    if (!_size) return emptyElem;
    return _stack[_size - 1];
}

template <typename T>
T Stack<T>::pop() {
    T emptyElem;
    if (!_size) return emptyElem;
    _size--;
    return _stack[_size];
}
template <typename T>
void Stack<T>::clear() {
    while (_size) pop();
}

template <typename T>
int Stack<T>::size() {
    return _size;
}

template <typename T>
bool Stack<T>::empty() {
    return _size == 0;
}

template <typename T>
QString Stack<T>::toString() {
    QString s = "[";
    for (int i = 0; i < _size; i++) {
        s.append(_stack[i]);
        if (i != _size - 1) s.append(", ");
    }
    return s;
}

template<>
QString Stack<double>::toString();

#endif // STACK_H
