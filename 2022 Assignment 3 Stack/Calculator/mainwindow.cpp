#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <cmath>

void MainWindow::refreshInputDisp() {
    ui->leInput->setText(expr.getExprStr());}

void MainWindow::refreshMidResultDisp() {
    QString tmpAns = expr.getMidAns();
    if (tmpAns.size()) {
        ui->leOutput->setText(tmpAns);
    }
}

void MainWindow::refreshResultDisp(){
    ui->leOutput->setText(expr.getResStr());
}

void MainWindow::refreshDebugDisp() {
    ui->leState->setText(expr.getStateStr());
    ui->leNumStack->setText(expr.getNumStackStr());
    ui->leOpStack->setText(expr.getOpStackStr());
}

void MainWindow::updateHistoryDisp() {
    ui->teHistory->setPlainText(
        expr.getExprStr().append("\n").append(
            expr.getResStr()
        ).append("\n").append("\n").append(ui->teHistory->toPlainText())
    );
}

void MainWindow::handleInput(char c) {
    switch(c) {
    case 'x':
        expr.clear();
        ui->leInput->clear();
        ui->leOutput->clear();
        break;
    case '<':{
        expr.backspace();
        refreshMidResultDisp();
        break;
    }
    default:
        expr.insert(c);
        refreshMidResultDisp();
        if (c == '#') {
            updateHistoryDisp();
            refreshResultDisp();
            expr.clear();
        }
    }
    refreshInputDisp();
    refreshDebugDisp();
}

void MainWindow::handleInput(Expression::Func f) {
    expr.func(f);
    refreshInputDisp();
    refreshMidResultDisp();
    refreshDebugDisp();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->leState->setText(expr.getStateStr());

//    expr = Expression();

    connect(ui->btn0,   &QPushButton::clicked, [=](){handleInput('0');});
    connect(ui->btn1,   &QPushButton::clicked, [=](){handleInput('1');});
    connect(ui->btn2,   &QPushButton::clicked, [=](){handleInput('2');});
    connect(ui->btn3,   &QPushButton::clicked, [=](){handleInput('3');});
    connect(ui->btn4,   &QPushButton::clicked, [=](){handleInput('4');});
    connect(ui->btn5,   &QPushButton::clicked, [=](){handleInput('5');});
    connect(ui->btn6,   &QPushButton::clicked, [=](){handleInput('6');});
    connect(ui->btn7,   &QPushButton::clicked, [=](){handleInput('7');});
    connect(ui->btn8,   &QPushButton::clicked, [=](){handleInput('8');});
    connect(ui->btn9,   &QPushButton::clicked, [=](){handleInput('9');});
    connect(ui->btnDot, &QPushButton::clicked, [=](){handleInput('.');});
    connect(ui->btnAdd, &QPushButton::clicked, [=](){handleInput('+');});
    connect(ui->btnSub, &QPushButton::clicked, [=](){handleInput('-');});
    connect(ui->btnMul, &QPushButton::clicked, [=](){handleInput('*');});
    connect(ui->btnDiv, &QPushButton::clicked, [=](){handleInput('/');});
    connect(ui->btnBracketL,  &QPushButton::clicked, [=](){handleInput('(');});
    connect(ui->btnBracketR,  &QPushButton::clicked, [=](){handleInput(')');});
    connect(ui->btnEqual,     &QPushButton::clicked, [=](){handleInput('#');});
    connect(ui->btnEqual2,    &QPushButton::clicked, [=](){handleInput('#');});
    connect(ui->btnClear,     &QPushButton::clicked, [=](){handleInput('x');});
    connect(ui->btnBackspace, &QPushButton::clicked, [=](){handleInput('<');});

    connect(ui->btnE,   &QPushButton::clicked, [=](){
        for (auto c:"2.71828")
            handleInput(c);
    });
    connect(ui->btnPi,   &QPushButton::clicked, [=](){
        for (auto c:"3.14159")
            handleInput(c);
    });
    connect(ui->btnLog,    &QPushButton::clicked, [=](){handleInput(Expression::Func::LOG);});
    connect(ui->btnLn,     &QPushButton::clicked, [=](){handleInput(Expression::Func::LN);});
    connect(ui->btnSquare, &QPushButton::clicked, [=](){handleInput(Expression::Func::SQUARE);});
    connect(ui->btnSqrt,   &QPushButton::clicked, [=](){handleInput(Expression::Func::SQRT);});
    connect(ui->btnSin,    &QPushButton::clicked, [=](){handleInput(Expression::Func::SIN);});
    connect(ui->btnCos,    &QPushButton::clicked, [=](){handleInput(Expression::Func::COS);});
    connect(ui->btnTan,    &QPushButton::clicked, [=](){handleInput(Expression::Func::TAN);});
    connect(ui->btnArcsin, &QPushButton::clicked, [=](){handleInput(Expression::Func::ARCSIN);});
    connect(ui->btnArccos, &QPushButton::clicked, [=](){handleInput(Expression::Func::ARCCOS);});
    connect(ui->btnArctan, &QPushButton::clicked, [=](){handleInput(Expression::Func::ARCTAN);});

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_leInput_textChanged(const QString &arg1)
{
    expr.setExprStr(arg1);
    refreshInputDisp();
    refreshMidResultDisp();
    refreshDebugDisp();
}

