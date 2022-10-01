/**
 * An Class for manipulating and calculating expressions.
 *
 * Author: AzurIce(XiaoBin)
 * Date: 2022-09-30
 *
 **/

#include "expression.h"
#include "stack.h"
#include <QDebug>
#include <cmath>

double calc(const double& num1, const double& num2, const char& op){
    switch(op){
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        return 0;
    }
}

int Expression::getOpPrior(char c) const {
    if (c == '*' || c == '/') return 1;
    return 0;
}

QString Expression::getExprStr() {
    return exprStr.replace("0-", "-");
}

void Expression::setExprStr(QString str) {
    exprStr = str;
    rebuildStacks();
}

QString Expression::getStateStr() {
    switch(state) {
    case INITIAL:
        return "INITIAL";
    case OPERATOR_INPUTED:
        return "OPERATOR_INPUTED";
    case INTEGER_INPUTED:
        return "INTEGER_INPUTED";
    case DECIMAL_POINT_INPUTED:
        return "DECIMAL_POINT_INPUTED";
    case DECIMAL_INPUTED:
        return "DECIMAL_INPUTED";
    case SUBEXPR_INPUTED:
        return "SUBEXPR_INPUTED";
    case FINISHED: // Never
        return "FINISHED";
    }
}

void Expression::rebuildStacks(){
    QString tmpStr = exprStr;
    op.clear();
    num.clear();
    exprStr.clear();
    setState(INITIAL);

    for(int i = 0; i < tmpStr.length(); i++){
        insert(tmpStr[i].toLatin1());
    }
}

void Expression::backspace() {
    exprStr = exprStr.left(exprStr.size() - 1);
    rebuildStacks();
}

void Expression::clear() {
    setState(INITIAL);
    num.clear();
    op.clear();
    exprStr.clear();
}

Expression::Expression(): state(INITIAL), decimalBase(0.1) {}

void Expression::setState(State state) {
    this->state = state;
}

void Expression::update(int opM = -1) {
    while(num.size() > 1 && !op.empty() && getOpPrior(op.top()) >= opM && op.top() != '('){
        double num2 = num.pop();
        double num1 = num.pop();
        char opc = op.pop();
        double res = calc(num1, num2, opc);
        num.push(res);
    }
}

void Expression::func(Func f) {
    double x = num.top();
    switch(f) {
    case LOG:
        x = log(x) / log(10);
        break;
    case LN:
        x = log(x);
        break;
    case SQUARE:
        x = x * x;
        break;
    case SQRT:
        x = sqrt(x);
        break;
    case SIN:
        x = sin(x);
        break;
    case COS:
        x = cos(x);
        break;
    case TAN:
        x = tan(x);
        break;
    case ARCSIN:
        x = asin(x);
        break;
    case ARCCOS:
        x = acos(x);
        break;
    case ARCTAN:
        x = atan(x);
        break;
    }

    if (abs(x - (int)x) < 0.0001) x = (int)x;

    switch(state) {
    case INTEGER_INPUTED:
    case DECIMAL_INPUTED:
    {
        int i = exprStr.size() - 1;
        while (i >= 0 && ((exprStr[i] >= '0' && exprStr[i] <= '9') || exprStr[i] == '.')) {
            i--;
        }
        exprStr = i ? exprStr.left(i + 1) : "";
        rebuildStacks();
        for (auto c:QString::number(x).toStdString())
            insert(c);
        break;
    }
    case SUBEXPR_INPUTED:
    {
        int cnt = 0;
        int i = exprStr.size() - 1;
        do {
            if (exprStr[i] == ')') cnt++;
            else if (exprStr[i] == '(') cnt--;
            i--;
        } while(i >= 0 && cnt);
        exprStr = exprStr.left(i + 1);
        rebuildStacks();
        for (auto c:QString::number(x).toStdString())
            insert(c);
        break;
    }
    default:
        return;
    }
}

void Expression::insert(char c) {
    if (state == FINISHED) {
        clear();
    }

    if (c == '#') {
        update();
        return;
    }
    if ('0' <= c && c <= '9') {
        switch(state) {
        case INITIAL:
        case OPERATOR_INPUTED:
            num.push(c - '0');
            setState(INTEGER_INPUTED);
            break;
        case INTEGER_INPUTED:
            num.push(num.pop() * 10 + c - '0');
            break;
        case DECIMAL_POINT_INPUTED:
            setState(DECIMAL_INPUTED);
        case DECIMAL_INPUTED:
            num.push(num.pop() + decimalBase * (c - '0'));
            decimalBase *= 0.1;
            break;
        case SUBEXPR_INPUTED: // INVALID
        case FINISHED: // Never
            return;
        }
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        switch(state) {
        case INITIAL: // NEGATE
            if (c == '-') {
                insert('0');
                insert('-');
            }
            return;
        case INTEGER_INPUTED: // OPERATOR
        case DECIMAL_INPUTED:
        case SUBEXPR_INPUTED:
            update(getOpPrior(c));
            op.push(c);
            setState(OPERATOR_INPUTED);
            break;
        case OPERATOR_INPUTED: // INVALID
        case DECIMAL_POINT_INPUTED: // INVALID
        case FINISHED: // Never
            return;
        }
    } else if (c == '(') {
        switch(state) {
        case INITIAL:
        case OPERATOR_INPUTED:
            op.push(c);
            setState(INITIAL);
            break;
        case INTEGER_INPUTED: // INVALID
        case DECIMAL_INPUTED: // INVALID
        case DECIMAL_POINT_INPUTED: // INVALID
        case FINISHED: // Never
        case SUBEXPR_INPUTED:
            return;
        }
    } else if (c == ')') {
        switch(state) {
        case INTEGER_INPUTED:
        case DECIMAL_INPUTED:
        case SUBEXPR_INPUTED:
            update();
            if (op.top() != '(') return;
            op.pop();
            setState(SUBEXPR_INPUTED);
            break;
        case INITIAL: // INVALID
        case OPERATOR_INPUTED: // INVALID
        case DECIMAL_POINT_INPUTED: // INVALID
        case FINISHED: // Never
            return;
        }
    } else if (c == '.') {
        switch(state) {
        case INTEGER_INPUTED:
            decimalBase = 0.1;
            setState(DECIMAL_POINT_INPUTED);
            break;
        case SUBEXPR_INPUTED: // INVALID
        case DECIMAL_INPUTED: // INVALID
        case INITIAL: // INVALID
        case OPERATOR_INPUTED: // INVALID
        case DECIMAL_POINT_INPUTED: // INVALID
        case FINISHED: // Never
            return;
        }
    } else {
        return;
    }
    exprStr.append(c);
}

QString Expression::getMidAns() {
    if (num.size() == 1) {
        return QString::number(num.top());
    }
    return "";
}

QString Expression::getResStr() {
    if(op.empty() && num.size() == 1)
        return QString::number(num.top());
    return "Syntax Error!";
}

QString Expression::getNumStackStr() {
    return num.toString();
}

QString Expression::getOpStackStr() {
    return op.toString();
}
