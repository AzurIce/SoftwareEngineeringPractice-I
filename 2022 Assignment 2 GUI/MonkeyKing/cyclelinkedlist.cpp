#include "cyclelinkedlist.h"
#include <iostream>

void CycleLinkedListNode::setNxt(CycleLinkedListNode* nxt) {
    _nxt = nxt;
}

// Getters
int CycleLinkedListNode::id() {
    return _id;
}

CycleLinkedListNode* CycleLinkedListNode::nxt(int offset) {
    auto o = this;
    for (int i = 1; i <= offset; i++) {
        o = o->nxt();
    }
    return o;
}

CycleLinkedListNode* CycleLinkedListNode::nxt() {
    return _nxt;
}


// ------ CycleLinkedList ------ //

CycleLinkedList::CycleLinkedList(int n) {
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
    for (int i = 1; i <= n; i++) {
        insert(i);
    }
    std::cout << "Created list of size " << n << ": ";
    printList();
}

void CycleLinkedList::insert(int id) {
    if (!_size) {
        _tail = _head = new CycleLinkedListNode(id);
        _head->setNxt(_head);
    } else {
        auto o = new CycleLinkedListNode(id, _head);
        _tail->setNxt(o);
        _tail = o;
    }
    _size++;
}

CycleLinkedListNode* CycleLinkedList::del(CycleLinkedListNode* o) {
    std::cout << "Deleting: " << o->id() << std::endl;
    auto pre = o->nxt(_size - 1);
    if (o == _tail) {
        _tail = pre;
    }
    if (o == _head) {
        _head = o->nxt();
    }
    pre->setNxt(o->nxt());
    auto nxt = o->nxt();
    delete o; _size--;
    return nxt;
}

int CycleLinkedList::size() {
    return _size;
}

CycleLinkedListNode* CycleLinkedList::head() {
    return _head;
}

CycleLinkedListNode* CycleLinkedList::tail() {
    return _tail;
}

// Debug

void CycleLinkedList::printList() {
    auto i = _head;
    do {
        std::cout << i->id() << " -> ";
        i = i->nxt();
    } while (i != _head);
    std::cout << "CYCLE" << std::endl;
}
