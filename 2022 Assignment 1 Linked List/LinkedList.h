#ifndef H_LINKED_LIST
#define H_LINKED_LIST

// A single node
class Node {
    public:
        Node(); // : k(0), p(0), next(nullptr) {}
        Node(const Node& o); // : k(o.k), p(o.p), next(o.next) {}
        Node(int k, int p); // : k(k), p(p), next(nullptr) {}

        void insert(Node *node);
        void printNode();
        // void print();

        int k;
        int p;
        Node* next;
};

// The whole LinkedList
class LinkedList {
    public:
        LinkedList(); // : headNode(Node()) {}
        LinkedList(const LinkedList& o); /*: headNode(Node()) {
            for (auto i = o.headNode.next; i; i = i->next) {
                insert(i->k, i->p);
            }
        }*/
        void clear();
        void insert(int k, int p);
        void printList();
        // void print();
        int getSize();

        Node headNode;
};

#endif
