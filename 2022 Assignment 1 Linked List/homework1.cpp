#include <iostream>
#include <cstdlib>
#include "Polynomial.h"

using namespace std;

int main() {
    freopen("input", "r", stdin);

    Polynomial a = Polynomial(), b = Polynomial();

    readPolynomial(a); readPolynomial(b);

    // a.printList();
    // b.printList();

    Polynomial b1 = Polynomial(b), b2 = Polynomial(b);

    freopen("output", "w", stdout);
    addPolynomial(a, b1);
    printPolynomial(b1);
    // b1.print();
    // cout << "ADD: " << endl;
    // b1.printList();

    mulPolynomial(a, b2);
    printPolynomial(b2);
    // b2.print();
    // cout << "MUL: " << endl;
    // b2.printList();

    return 0;
}
