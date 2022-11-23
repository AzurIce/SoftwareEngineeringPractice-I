#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QQuickWidget>
#include "models/InterestPointList.h"
#include "graphics/InterestPointGraphicsItem.h"
#include <QDebug>
#include <QGeoCoordinate>

double getDisY(QGeoCoordinate &coord1, QGeoCoordinate &coord2) {
    QGeoCoordinate m(coord1.latitude(), coord2.longitude());
    return coord2.distanceTo(m);
}

double getDisX(QGeoCoordinate &coord1, QGeoCoordinate &coord2) {
    QGeoCoordinate m(coord1.latitude(), coord2.longitude());
    return coord1.distanceTo(m);
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene);

    ui->quickWidget->setFixedWidth(300);
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget->setAttribute(Qt::WA_TranslucentBackground);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setSource(QUrl::fromLocalFile(":myqml/ui/test.qml"));

    auto heiheiheiha = (QObject *) ui->quickWidget->rootObject();
    qDebug() << "heiheiheiha: " << heiheiheiha;
    connect(heiheiheiha, SIGNAL(mySelect(int)), this, SLOT(onSelect(int)));
    connect(heiheiheiha, SIGNAL(myCheck(int, bool)), this, SLOT(onCheck(int, bool)));

    QGeoCoordinate p1(39.954197, 116.335786), p2(39.949254, 116.348725);

    const double mapWidth = getDisX(p1, p2);
    const double mapHeight = getDisY(p1, p2);

    auto mapPixmap = QPixmap(":/res/res/map.png");
    auto mapItem = new QGraphicsPixmapItem(mapPixmap);
    mapItem->setScale(mapWidth /  mapPixmap.width());
    mapItem->setPos(0, 0);
    ui->graphicsView->scene()->addItem(mapItem);

    for (InterestPoint &i: interestPointList.interestPoints) {
        QGeoCoordinate p(i.lat(), i.lng());
        auto interestPoint = new InterestPointGraphicsItem(i.name(), getDisX(p1, p), getDisY(p1, p));
        interestPoints.push_back(interestPoint);
        ui->graphicsView->scene()->addItem(interestPoint);
    }
    interestPoints[0]->selected = true;
    ui->graphicsView->viewport()->update();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onSelect(int index) {
    for (auto interestPoint: interestPoints)
        interestPoint->selected = false;
    qDebug() << "OnSelect:" << index;
    interestPoints[index]->selected = true;
    ui->graphicsView->viewport()->update();
}

void MainWindow::onCheck(int index, bool checked) {
    interestPoints[index]->checked = checked;
    qDebug() << "OnToggle:" << index << checked;
    ui->graphicsView->viewport()->update();
}
