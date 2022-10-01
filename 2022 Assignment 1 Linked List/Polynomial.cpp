#include <iostream>
#include "Polynomial.h"

using namespace std;

void printPolynomial(Polynomial& x) {
    cout << x.getSize() << " ";
    for (auto i = x.headNode.next; i; i = i -> next) {
        cout << i->k << " " << i->p << " ";
    }
    cout << endl;
}

void readPolynomial(Polynomial& x) {
    int n;
    cin >> n;
    for (int i = 1, k, p; i <= n; i++) {
        cin >> k >> p;
        x.insert(k, p);
    }
}

// Add x to y
void addPolynomial(const Polynomial &x, Polynomial& y) {
    auto i = x.headNode.next;
    auto j = y.headNode.next;

    auto prej = &y.headNode;
    while (i && j) {
        if (i->p > j->p) {
            y.insert(i->k, i->p);
            i = i->next;
        } else if (i->p < j->p) {
            prej = j;
            j = j->next;
        } else {
            j->k += i->k;
            if (j->k == 0) {
                prej -> next = j -> next;
                auto del = j;
                j = j->next;
                delete del;
            }
            i = i->next;
        }
    }

    while (i) {
        y.insert(i->k, i->p);
        i = i->next;
    }

}

// Multiply x to y
void mulPolynomial(const Polynomial x, Polynomial& y) {
    Polynomial yy = Polynomial(y);
    y.clear();

    // y.printList();
    for (auto j = &yy.headNode; j->next; j = j->next) {
        auto &&target = j->next;
        auto tmp = Polynomial();
        for (auto i = x.headNode.next; i; i = i->next) {
            // i->printNode();
            tmp.insert(i->k * target->k, i->p + target->p);
        }
        // tmp.printList();
        addPolynomial(tmp, y);
    }

}
