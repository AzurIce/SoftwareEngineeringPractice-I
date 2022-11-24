#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QQuickWidget>
//#include "models/InterestPointList.h"
#include "graphics/InterestPointGraphicsItem.h"
#include "graphics/Edge.h"
#include <QDebug>
#include <QNetworkReply>
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->btnShowShortestPath1->setDisabled(true);
    ui->btnShowShortestPath2->setDisabled(true);

    connect(ui->btnCancelStart, &QPushButton::clicked, this, [=]() {
        ui->lineEdit->clear();
        startPoint = -1;
        ui->btnShowShortestPath1->setDisabled(true);
        ui->btnShowShortestPath2->setDisabled(true);
    });

    connect(ui->btnCancelEnd, &QPushButton::clicked, this, [=]() {
        ui->lineEdit_2->clear();
        endPoint = -1;
        ui->btnShowShortestPath1->setDisabled(true);
    });

    connect(ui->btnSetStart, &QPushButton::clicked, this, [=]() {
        int selected = 0;
        for (auto &i: interestPoints) {
            if (i->m_selected) {
                selected = i->m_id;
                break;
            }
        }
        if (endPoint == selected) return;

        startPoint = selected;
        ui->lineEdit->setText(QString::number(selected) + interestPoints[selected]->m_name);
        if (endPoint != -1) ui->btnShowShortestPath1->setDisabled(false);
        ui->btnShowShortestPath2->setDisabled(false);
    });

    connect(ui->btnSetEnd, &QPushButton::clicked, this, [=]() {
        int selected = 0;
        for (auto &i: interestPoints) {
            if (i->m_selected) {
                selected = i->m_id;
                break;
            }
        }
        if (startPoint == selected) return;
        endPoint = selected;
        ui->lineEdit_2->setText(QString::number(selected) + interestPoints[selected]->m_name);
        if (startPoint != -1) ui->btnShowShortestPath1->setDisabled(false);
    });

    // Initialize GraphicsView
    ui->graphicsView->setScene(new QGraphicsScene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setRenderHint(QPainter::RenderHint::Antialiasing);

    connect(ui->slider, &QSlider::valueChanged, this, [=](int value) {
        QTransform matrix;
        matrix.scale(value / 100.0, value / 100.0);
        ui->graphicsView->setTransform(matrix);
    });

    connect(ui->btnShowShortestPath1, &QPushButton::clicked, this, [=]() {
        // 最短路径
        std::vector<int> tmpPoints;
        std::vector<Edge *> tmpEdges;
        std::vector<bool> mark(15, false);
        mark[startPoint] = true;
        std::vector<int> pointVec;
        std::vector<Edge *> edgeVec;
        double ansDis = 2147483648;

        dfs1(startPoint, 0, tmpPoints, tmpEdges, mark, ansDis, pointVec, edgeVec);
        ui->plainTextEdit->appendPlainText(QString("从 [%1:%2] 到 [%3:%4] 的最短路径长度为 %5：")
                                                   .arg(startPoint).arg(interestPoints[startPoint]->m_name)
                                                   .arg(endPoint).arg(interestPoints[endPoint]->m_name)
                                                   .arg(ansDis));
        QString way = QString("[%1:%2] ").arg(startPoint).arg(interestPoints[startPoint]->m_name);
        for (auto &i: interestPoints) {
            i->m_passed = false;
        }
        interestPoints[startPoint]->m_passed = true;
        for (auto i: pointVec) {
            interestPoints[i]->m_passed = true;
            way.append(QString("[%1:%2] ").arg(i).arg(interestPoints[i]->m_name));
        }
        for (auto e: edges) {
            e->m_selected = false;
        }
        for (auto e: edgeVec) {
            e->m_selected = true;
        }
        ui->plainTextEdit->appendPlainText(way);
        ui->graphicsView->viewport()->update();
    });

    connect(ui->btnShowShortestPath2, &QPushButton::clicked, this, [=]() {
        // 最短遍历路径
        std::vector<int> tmpPoints;
        std::vector<Edge *> tmpEdges;
        std::vector<bool> mark(15, false);
        mark[startPoint] = true;
        std::vector<int> pointVec;
        std::vector<Edge *> edgeVec;
        double ansDis = 2147483648;
        dfs2(startPoint, 0, tmpPoints, tmpEdges, mark, ansDis, pointVec, edgeVec);
        ui->plainTextEdit->appendPlainText(QString("以 [%1:%2] 为起点游遍选定景点的最短路径长度为 %3：")
                                                   .arg(startPoint).arg(interestPoints[startPoint]->m_name)
                                                   .arg(ansDis));
        QString way = QString("[%1:%2] ").arg(startPoint).arg(interestPoints[startPoint]->m_name);
        for (auto &i: interestPoints) {
            i->m_passed = false;
        }
        interestPoints[startPoint]->m_passed = true;
        for (auto i: pointVec) {
            interestPoints[i]->m_passed = true;
            way.append(QString("[%1:%2] ").arg(i).arg(interestPoints[i]->m_name));
        }
        for (auto e: edges) {
            e->m_selected = false;
        }
        for (auto e: edgeVec) {
            e->m_selected = true;
        }
        ui->plainTextEdit->appendPlainText(way);
        ui->graphicsView->viewport()->update();
    });

    // Initialize QuickWidget
    ui->quickWidget->setFixedWidth(320);
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget->setAttribute(Qt::WA_TranslucentBackground);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setSource(QUrl::fromLocalFile(":myqml/ui/test.qml"));

    auto heiheiheiha = (QObject *) ui->quickWidget->rootObject();
    connect(heiheiheiha, SIGNAL(mySelect(int)), this, SLOT(onSelect(int)));
    connect(heiheiheiha, SIGNAL(myCheck(int, bool)), this, SLOT(onCheck(int, bool)));

    // Initialize map image
    const int startI = 107893;
    const int startJ = 49643;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            auto mapItem = new QGraphicsPixmapItem(
                    QPixmap(QString(":/res/res/map/17/%1/%2.png").arg(i + startI).arg(j + startJ)));
            mapItem->setPos(i * 255, j * 255);
            ui->graphicsView->scene()->addItem(mapItem);
        }
    }

    for (auto &interestPoint: interestPoints) {
        ui->graphicsView->scene()->addItem(interestPoint);
    }

    initBasicGraph();
    for (int i = 1; i < edges.size(); i++) {
        ui->graphicsView->scene()->addItem(edges[i]);
    }
}


void
MainWindow::dfs1(int x, double dd, std::vector<int> &tmpPoints, std::vector<Edge *> &tmpEdges, std::vector<bool> &mark,
                 double &ansDis, std::vector<int> &pointVec, std::vector<Edge *> &edgeVec) {
    if (x == endPoint) {
        if (dd < ansDis) {
            ansDis = dd;
            pointVec.clear();
            pointVec.insert(pointVec.begin(), tmpPoints.begin(), tmpPoints.end());
            edgeVec.clear();
            edgeVec.insert(edgeVec.begin(), tmpEdges.begin(), tmpEdges.end());
        }
        return;
    }
    for (auto i = h[x]; i; i = edges[i]->next) {
        if (mark[edges[i]->destNode()->m_id]) continue;
        mark[edges[i]->destNode()->m_id] = true;
        tmpPoints.push_back(edges[i]->destNode()->m_id);
        tmpEdges.push_back(edges[i]);
        dfs1(edges[i]->destNode()->m_id, dd + edges[i]->w, tmpPoints, tmpEdges, mark, ansDis, pointVec, edgeVec);
        tmpPoints.pop_back();
        tmpEdges.pop_back();
        mark[edges[i]->destNode()->m_id] = false;
    }
}

void
MainWindow::dfs2(int x, double dd, std::vector<int> &tmpPoints, std::vector<Edge *> &tmpEdges, std::vector<bool> &mark,
                 double &ansDis, std::vector<int> &pointVec, std::vector<Edge *> &edgeVec) {
    bool final = true;
    for (int i = 0; i < interestPoints.size(); i++) {
        if (interestPoints[i]->m_checked) {
//            qDebug() << QString("mark[%1]: %2").arg(i).arg(mark[i]);
            if (!mark[i]) {
                final = false;
                break;
            }
        }
    }
    if (final) {
        if (dd < ansDis) {
            ansDis = dd;
            pointVec.clear();
            pointVec.insert(pointVec.begin(), tmpPoints.begin(), tmpPoints.end());
            edgeVec.clear();
            edgeVec.insert(edgeVec.begin(), tmpEdges.begin(), tmpEdges.end());
        }
        return;
    }
    for (auto i = h[x]; i; i = edges[i]->next) {
        if (mark[edges[i]->destNode()->m_id]) continue;
        mark[edges[i]->destNode()->m_id] = true;
        tmpPoints.push_back(edges[i]->destNode()->m_id);
        tmpEdges.push_back(edges[i]);
        dfs2(edges[i]->destNode()->m_id, dd + edges[i]->w, tmpPoints, tmpEdges, mark, ansDis, pointVec, edgeVec);
        tmpPoints.pop_back();
        tmpEdges.pop_back();
        mark[edges[i]->destNode()->m_id] = false;
    }
}


MainWindow::~MainWindow() {
    delete ui;
    delete manager;
}

void MainWindow::onSelect(int index) {
    for (auto interestPoint: interestPoints)
        interestPoint->m_selected = false;
    qDebug() << "OnSelect:" << index;
    interestPoints[index]->m_selected = true;
    ui->graphicsView->viewport()->update();
}

void MainWindow::onCheck(int index, bool checked) {
    interestPoints[index]->m_checked = checked;
    qDebug() << "OnToggle:" << index << checked;
    ui->graphicsView->viewport()->update();
}

void MainWindow::initBasicGraph() {
    addTwoWayEdge(10, 11, 148);
    addTwoWayEdge(11, 9, 119);
    addTwoWayEdge(9, 7, 151);
    addTwoWayEdge(9, 8, 154);
    addTwoWayEdge(10, 8, 190);
    addTwoWayEdge(7, 2, 173);
    addTwoWayEdge(2, 11, 180);
    addTwoWayEdge(2, 1, 132);
    addTwoWayEdge(1, 3, 146);
    addTwoWayEdge(2, 3, 211);
    addTwoWayEdge(3, 4, 136);
    addTwoWayEdge(4, 6, 192);
    addTwoWayEdge(0, 6, 141);
    addTwoWayEdge(6, 5, 42);
    addTwoWayEdge(5, 0, 137);
    addTwoWayEdge(9, 5, 224);
    addTwoWayEdge(3, 5, 136);
    addTwoWayEdge(8, 5, 234);
    for (auto &e: edges) {
        ui->graphicsView->scene()->addItem(e);
    }
}

//void MainWindow::resizeEvent(QResizeEvent *event) {
//    graphicsViewSize = event->size();
//    qDebug() << "ResizeEvent:" << event->size();
//    QWidget::resizeEvent(event);
//}
