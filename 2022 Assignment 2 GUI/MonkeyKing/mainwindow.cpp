#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cyclelinkedlist.h"
#include "node.h"
#include "edge.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->verticalLayoutWidget);
    ui->gvMain->setScene(new QGraphicsScene());
    p = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::debugPrint(int x) {
    ui->teDebug->setText(
        ui->teDebug->toPlainText().append(QString::number(x))
    );
}

void MainWindow::debugPrint(const QString &text) {
    ui->teDebug->setText(
        ui->teDebug->toPlainText().append(text)
    );
}

void drawList(CycleLinkedList* list, QGraphicsView* view) {
    auto scene = view->scene();
    scene->clear();
    if (!list->size()) return;

    int cnt = 0;
    double theta = 2 * 3.14 / list->size();
    Node* preNode = new Node(view, list->head()->id());
    Node* headNode = preNode;
    scene->addItem(preNode);

    int r = 100;
    preNode->setPos(r * cos(cnt * theta), r * sin(cnt * theta));
    cnt++;

    if (list->size() == 1) return;

    auto i = list->head();
    do {
        auto node = new Node(view, i->nxt()->id());
        node->setPos(r * cos(cnt * theta), r * sin(cnt * theta));
        scene->addItem(node);
        scene->addItem(new Edge(preNode, node));
//        std::cout << i->id() << " -> ";
        i = i->nxt(); preNode = node; cnt++;
    } while (i->nxt() != list->head());

    scene->addItem(new Edge(preNode, headNode));
}

void MainWindow::on_btnStart_clicked()
{
    bool flag = 1;
//    n = ui->tvTotal->text().toInt();
    n = ui->tvTotal->text().toInt(&flag);
    if (!flag) return;
//    k = ui->tvIndex->text().toInt();
    k = ui->tvIndex->text().toInt(&flag);
    if (!flag) return;
//    n = 6;
//    k = 2;

    list = CycleLinkedList(n);
    p = list.head();

    ui->teDebug->setText("");
    drawList(&list, ui->gvMain);
}


void MainWindow::on_btnStep_clicked()
{
    if (!p) return;
    if (list.size() > 1) {
        p = p->nxt(k - 1);
        debugPrint("🐒[");
        debugPrint(p->id());
        debugPrint("] ");
        p = list.del(p);
        drawList(&list, ui->gvMain);
    }
}

