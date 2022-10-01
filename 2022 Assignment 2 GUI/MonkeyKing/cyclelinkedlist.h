#ifndef CYCLELINKEDLIST_H
#define CYCLELINKEDLIST_H

class CycleLinkedListNode {
public:
    CycleLinkedListNode();
    CycleLinkedListNode(int id): _id(id) {};
    CycleLinkedListNode(int id, CycleLinkedListNode* nxt): _id(id), _nxt(nxt) {};

    // Getters
    int id();
    CycleLinkedListNode* nxt(int offset);
    CycleLinkedListNode* nxt();
    // Setters
    void setNxt(CycleLinkedListNode* nxt);
private:
    int _id;
    CycleLinkedListNode* _nxt;
};

class CycleLinkedList {
public:
    CycleLinkedList(): _size(0), _head(nullptr), _tail(nullptr) {};
    CycleLinkedList(int n);
    void insert(int id);
    CycleLinkedListNode* del(CycleLinkedListNode* o);

    // Getters
    int size();
    CycleLinkedListNode* head();
    CycleLinkedListNode* tail();

    // Debug
    void printList();
private:
    int _size;
    CycleLinkedListNode* _head;
    CycleLinkedListNode* _tail;
};

#endif // CYCLELINKEDLIST_H
