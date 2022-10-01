#include <iostream>
#include "LinkedList.h"

using namespace std;

// -- Node --
// Constructors
Node::Node() : k(0), p(0), next(nullptr) {}
Node::Node(const Node& o) : k(o.k), p(o.p), next(o.next) {}
Node::Node(int k, int p): k(k), p(p), next(nullptr) {}

void Node::insert(Node *node) {
    node->next = next;
    next = node;
}

void Node::printNode() {
    cout << "Node<k: " << k << ", p: " << p << ">";
}

// -- LinkedList --
// Constructors
LinkedList::LinkedList() : headNode(Node()) {}
LinkedList::LinkedList(const LinkedList& o) : headNode(Node()) {
    for (auto i = o.headNode.next; i; i = i->next) {
        insert(i->k, i->p);
    }
}

int LinkedList::getSize() {
    int cnt = 0;
    for (auto i = headNode.next; i; i = i->next) {
        cnt++;
    }
    return cnt;
}

void LinkedList::clear() {
    auto del = headNode.next;
    for (auto i = del->next; i; i = i->next) {
        delete del;
        del = i;
    }
    headNode.next = nullptr;
}

void LinkedList::insert(int k, int p) {
    auto pos = &headNode;
    while (pos -> next && pos -> next -> p > p) pos = pos -> next;
    pos -> insert(new Node(k, p));
}

void LinkedList::printList() {
    for (auto i = headNode.next; i; i = i -> next) {
        i->printNode();
        cout << " -> ";
    }
    cout << "null" << endl;
}

// void LinkedList::print() {
//     cout << getSize() << " ";
//     for (auto i = headNode.next; i; i = i -> next) {
//         i->print();
//     }
//     cout << endl;
// }
