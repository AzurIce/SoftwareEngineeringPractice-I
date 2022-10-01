#include "stack.h"
#include <cstdlib>

template <typename T>
QString Stack<T>::toString() {
    QString s;
    for (int i = 0; i < _size; i++) {
        s.append(_stack[i]);
    }
    return s;
}

template <typename T>
Stack<T>::Stack(): _capacity(DEFAULT_CAP), _size(0) {
    _stack = (T*) malloc(sizeof(T) * _capacity);
    if (!_stack) {
        // Error
    }
}

template <typename T>
Stack<T>::Stack(int _capacity): _capacity(_capacity), _size(0) {
    _stack = (T*) malloc(sizeof(T) * _capacity);
    if (!_stack) {
        // Error
    }
}

template <typename T>
Stack<T>::~Stack() {
    free(_stack);
}

template <typename T>
bool Stack<T>::resize(int _capacity) {
    T* newStack;
    newStack = (T*) realloc(_stack, sizeof(T) * _capacity);
    if (newStack) {
        this->_capacity = _capacity;
        _stack = newStack;
        return true;
    }
    return false;
}

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
T Stack<T>::pop() {
    T emptyElem;
    if (!_size) return emptyElem;
    _size--;
    return _stack[_size];
}

template <typename T>
T Stack<T>::top() {
    T emptyElem;
    if (!_size) return emptyElem;
    return _stack[_size - 1];
}

template <typename T>
int Stack<T>::size() {
    return _size;
}

template <typename T>
bool Stack<T>::empty() {
    return _size == 0;
}
