#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QQuickWidget>
//#include "models/InterestPointList.h"
#include "graphics/InterestPointGraphicsItem.h"
#include "graphics/Edge.h"
#include <QDebug>
#include <QNetworkReply>
#include <QSlider>
#include <storage/Database.h>
#include <QTextToSpeech>
//#include <Set>

void MainWindow::initData() {
    auto interestPointsData = Database::getInstance().getInterestPointsData();
    for (const auto& data: interestPointsData) {
        interestPoints.push_back(new InterestPointGraphicsItem(data));
    }

    auto edgesData = Database::getInstance().getEdgesData();
    for (const auto& data: edgesData) {
        addTwoWayEdge(data.x, data.y, data.w);
    }
}

void MainWindow::initGraphicsView() {
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

    // Initialize interestPoints
    for (auto &interestPoint: interestPoints) {
        ui->graphicsView->scene()->addItem(interestPoint);
    }

//    std::set<Edge *> es;
    // Initialize edges
    for (auto &e: edges) {
//        if (es.count(e2e[e]) || es.count(e)) continue;
//        es.insert(e);
        ui->graphicsView->scene()->addItem(e);
    }
    ui->graphicsView->viewport()->update();
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->btnShowShortestPath1->setDisabled(true);
    ui->btnShowShortestPath2->setDisabled(true);

    // Initialize GraphicsView
    ui->graphicsView->setScene(new QGraphicsScene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setRenderHint(QPainter::RenderHint::Antialiasing);

    initData();
    initGraphicsView();

    initSignalAndSlots();

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
}


void MainWindow::dfs1(int x, double dd, std::vector<int> &tmpPoints, std::vector<Edge *> &tmpEdges, std::vector<bool> &mark,
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
        InterestPointData &destNodeData = edges[i]->destNode()->data;
        if (mark[destNodeData.id]) continue;
        mark[destNodeData.id] = true;
        tmpPoints.push_back(destNodeData.id);
        tmpEdges.push_back(edges[i]);
        dfs1(destNodeData.id, dd + edges[i]->w, tmpPoints, tmpEdges, mark, ansDis, pointVec, edgeVec);
        tmpPoints.pop_back();
        tmpEdges.pop_back();
        mark[destNodeData.id] = false;
    }
}

void
MainWindow::dfs2(int x, double dd, std::vector<int> &tmpPoints, std::vector<Edge *> &tmpEdges, std::vector<bool> &mark,
                 double &ansDis, std::vector<int> &pointVec, std::vector<Edge *> &edgeVec) {
    bool final = true;
    for (int i = 0; i < interestPoints.size(); i++) {
        if (interestPoints[i]->data.checked) {
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
        InterestPointData &destNodeData = edges[i]->destNode()->data;
        if (mark[destNodeData.id]) continue;
        mark[destNodeData.id] = true;
        tmpPoints.push_back(destNodeData.id);
        tmpEdges.push_back(edges[i]);
        dfs2(destNodeData.id, dd + edges[i]->w, tmpPoints, tmpEdges, mark, ansDis, pointVec, edgeVec);
        tmpPoints.pop_back();
        tmpEdges.pop_back();
        mark[destNodeData.id] = false;
    }
}


MainWindow::~MainWindow() {
    delete ui;
    delete speech;
//    delete manager;
}

void MainWindow::onSelect(int index) {
    for (auto interestPoint: interestPoints)
        interestPoint->data.selected = false;
//    qDebug() << "OnSelect:" << index;

    if (ui->checkBox->isChecked())
        speech->say(interestPoints[index]->data.name + ", " + interestPoints[index]->data.desc);
    ui->plainTextEdit->setPlainText(interestPoints[index]->data.desc);
    interestPoints[index]->data.selected = true;
    ui->graphicsView->viewport()->update();
}

void MainWindow::onCheck(int index, bool checked) {
    interestPoints[index]->data.checked = checked;
//    qDebug() << "OnToggle:" << index << checked;
    ui->graphicsView->viewport()->update();
}

void MainWindow::initSignalAndSlots() {
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
            if (i->data.selected) {
                selected = i->data.id;
                break;
            }
        }
        if (endPoint == selected) return;

        startPoint = selected;
        ui->lineEdit->setText(QString::number(selected) + interestPoints[selected]->data.name);
        if (endPoint != -1) ui->btnShowShortestPath1->setDisabled(false);
        ui->btnShowShortestPath2->setDisabled(false);
    });

    connect(ui->btnSetEnd, &QPushButton::clicked, this, [=]() {
        int selected = 0;
        for (auto &i: interestPoints) {
            if (i->data.selected) {
                selected = i->data.id;
                break;
            }
        }
        if (startPoint == selected) return;
        endPoint = selected;
        ui->lineEdit_2->setText(QString::number(selected) + interestPoints[selected]->data.name);
        if (startPoint != -1) ui->btnShowShortestPath1->setDisabled(false);
    });

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
                                                   .arg(startPoint).arg(interestPoints[startPoint]->data.name)
                                                   .arg(endPoint).arg(interestPoints[endPoint]->data.name)
                                                   .arg(ansDis));
        QString way = QString("[%1:%2] ").arg(startPoint).arg(interestPoints[startPoint]->data.name);
        for (auto &i: interestPoints) {
            i->m_passed = false;
        }
        interestPoints[startPoint]->m_passed = true;
        for (auto i: pointVec) {
            interestPoints[i]->m_passed = true;
            way.append(QString("[%1:%2] ").arg(i).arg(interestPoints[i]->data.name));
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
                                                   .arg(startPoint).arg(interestPoints[startPoint]->data.name)
                                                   .arg(ansDis));
        QString way = QString("[%1:%2] ").arg(startPoint).arg(interestPoints[startPoint]->data.name);
        for (auto &i: interestPoints) {
            i->m_passed = false;
        }
        interestPoints[startPoint]->m_passed = true;
        for (auto i: pointVec) {
            interestPoints[i]->m_passed = true;
            way.append(QString("[%1:%2] ").arg(i).arg(interestPoints[i]->data.name));
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

    connect(ui->checkBox, &QCheckBox::stateChanged, this, [=]() {
       speech->stop();
    });
}
