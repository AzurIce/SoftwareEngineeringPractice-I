/**
 * An Class for manipulating and calculating expressions.
 *
 * Author: AzurIce(XiaoBin)
 * Date: 2022-09-30
 *
 **/

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QString>
#include <map>
#include "stack.h"

class Expression {
public:
    // State defination for state machine
    enum State {
        INITIAL,
        OPERATOR_INPUTED,
        INTEGER_INPUTED,
        DECIMAL_POINT_INPUTED,
        DECIMAL_INPUTED,
        SUBEXPR_INPUTED,
        FINISHED
    };

    // Advance functios
    enum Func {
       LOG, LN, SQUARE, SQRT, SIN, COS, TAN, ARCSIN, ARCCOS, ARCTAN
    };

    Expression();
    void insert(char c);
    void backspace();
    void clear();
    void func(Func f);

    void setExprStr(QString str);
    QString getExprStr();
    QString getStateStr();
    QString getResStr();
    QString getMidAns();
    QString getNumStackStr();
    QString getOpStackStr();
private:
    State state;

    QString exprStr;
    Stack<char> op;
    Stack<double> num;
    double decimalBase;

    int getOpPrior(char c) const;
//    std::map<char, int> opMap;

    void update(int opM);
    void setState(State state);
    void rebuildStacks();
};

#endif // EXPRESSION_H
