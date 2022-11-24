#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include "graphics/InterestPointGraphicsItem.h"
#include "graphics/Edge.h"
#include <QNetworkAccessManager>
#include <QGeoCoordinate>
#include <QTextToSpeech>
//#include <Map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:

    void onSelect(int index);

    void onCheck(int index, bool checked);

private:
    Ui::MainWindow *ui;
    std::vector<InterestPointGraphicsItem *> interestPoints;
    std::vector<Edge *> edges;
    QTextToSpeech *speech = new QTextToSpeech(this);

    int startPoint = -1;
    int endPoint = -1;

    void initData();
    void initGraphicsView();
    void initSignalAndSlots();

    int h[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//    std::map<Edge *, Edge*> e2e;

    void addEdge(int f, int t, double w) {
        InterestPointGraphicsItem *ff, *tt;
        for (auto &interestPoint: interestPoints) {
            if (interestPoint->data.id == f) ff = interestPoint;
            if (interestPoint->data.id == t) tt = interestPoint;
        }
        auto e = new Edge(ff, tt, w, h[f]);
        edges.push_back(e);
        h[f] = edges.size() - 1;
    }

    void addTwoWayEdge(int x, int y, double w) {
        addEdge(x, y, w);
        addEdge(y, x, w);
//        e2e[edges[edges.size() - 1]] = edges[edges.size()];
//        e2e[edges[edges.size()]] = edges[edges.size() - 1];
    }

    void dfs1(int x, double dd, std::vector<int> &tmpPoints, std::vector<Edge *> &tmpEdges, std::vector<bool> &mark,
              double &ansDis, std::vector<int> &pointVec, std::vector<Edge *> &edgeVec);

    void dfs2(int x, double dd, std::vector<int> &tmpPoints, std::vector<Edge *> &tmpEdges, std::vector<bool> &mark,
              double &ansDis, std::vector<int> &pointVec, std::vector<Edge *> &edgeVec);
};

#endif // MAINWINDOW_H
