#ifndef H_POLYNOMIAL
#define H_POLYNOMIAL

#include "LinkedList.h"

typedef LinkedList Polynomial;

void printPolynomial(Polynomial& x);
void readPolynomial(Polynomial& x);
void addPolynomial(const Polynomial &x, Polynomial& y);
void mulPolynomial(const Polynomial x, Polynomial& y);

#endif
