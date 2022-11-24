#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include "models/InterestPointList.h"
#include "graphics/InterestPointGraphicsItem.h"
#include "graphics/Edge.h"
#include <QNetworkAccessManager>
#include <QGeoCoordinate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:

    void onSelect(int index);

    void onCheck(int index, bool checked);

private:
    Ui::MainWindow *ui;
    std::vector<InterestPointGraphicsItem *> interestPoints = {
            new InterestPointGraphicsItem(0, "逸夫教学楼", 39.951676, 116.344720, true),
            new InterestPointGraphicsItem(1, "思源楼", 39.951491, 116.340831),
            new InterestPointGraphicsItem(2, "思源西楼", 39.951261, 116.339892),
            new InterestPointGraphicsItem(3, "思源东楼", 39.951577, 116.341791),
            new InterestPointGraphicsItem(4, "明湖", 39.952038, 116.342272),
            new InterestPointGraphicsItem(5, "芳华园", 39.951512, 116.343216),
            new InterestPointGraphicsItem(6, "图书馆", 39.952006, 116.343409),
            new InterestPointGraphicsItem(7, "学活", 39.950426, 116.338602),
            new InterestPointGraphicsItem(8, "世纪钟", 39.950402, 116.342154),
            new InterestPointGraphicsItem(9, "积秀园", 39.950394, 116.340078),
            new InterestPointGraphicsItem(10, "南门", 39.94927, 116.341475),
            new InterestPointGraphicsItem(11, "天佑会堂", 39.950052, 116.340568)
    };
    std::vector<Edge *> edges;

    int startPoint = -1;
    int endPoint = -1;


    int h[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    void addEdge(int f, int t, int w) {
        InterestPointGraphicsItem *ff, *tt;
        for (int i = 0; i < interestPoints.size(); i++) {
//            qDebug() << interestPoints[i]->m_id;
            if (interestPoints[i]->m_id == f) {
                ff = interestPoints[i];
            }
            if (interestPoints[i]->m_id == t) {
                tt = interestPoints[i];
            }
        }
        auto e = new Edge(ff, tt, w, h[f]);
        edges.push_back(e);
        h[f] = edges.size() - 1;
    }

    void addTwoWayEdge(int x, int y, int w) {
        addEdge(x, y, w);
        addEdge(y, x, w);
    }

    InterestPointList interestPointList;
    QNetworkAccessManager *manager = new QNetworkAccessManager;

    void initBasicGraph();

    void dfs1(int x, double dd, std::vector<int> &tmpPoints, std::vector<Edge *> &tmpEdges, std::vector<bool> &mark,
              double &ansDis, std::vector<int> &pointVec, std::vector<Edge *> &edgeVec);
    void dfs2(int x, double dd, std::vector<int> &tmpPoints, std::vector<Edge *> &tmpEdges, std::vector<bool> &mark,
              double &ansDis, std::vector<int> &pointVec, std::vector<Edge *> &edgeVec);
};

#endif // MAINWINDOW_H
