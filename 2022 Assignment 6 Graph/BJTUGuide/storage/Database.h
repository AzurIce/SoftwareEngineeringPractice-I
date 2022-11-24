//
// Created by AzurIce on 2022/11/23.
//

#ifndef BJTUGUIDE_DATABASE_H
#define BJTUGUIDE_DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <models/InterestPointData.h>
#include <models/EdgeData.h>

const InterestPointData defaultInterestPointsData[] = {
        InterestPointData(0, "逸夫教学楼",
                          "软件学院的楼，同时也是研究生院所在，二楼有机房，三楼有个咖啡店，逸夫的教室可以说是全校插座最多的教室了",
                          39.951676, 116.344720, true),
        InterestPointData(1, "思源楼", "最中间的一座教学楼，有好多好多好多好多好多好多层",
                          39.951491, 116.340831),
        InterestPointData(2, "思源西楼", "法学院的楼，同时也是物工的？",
                          39.951261, 116.339892),
        InterestPointData(3, "思源东楼", "经管学院的楼",
                          39.951577, 116.341791),
        InterestPointData(4, "明湖", "就，湖，明湖上面的亭子叫做爱知亭，湖里有很多的鸭子，这些鸭子冬天都去了哪呢？",
                          39.952038, 116.342272),
        InterestPointData(5, "芳华园", "花花草草木木",
                          39.951512, 116.343216),
        InterestPointData(6, "图书馆", "书书书书书书书",
                          39.952006, 116.343409),
        InterestPointData(7, "学活", "《一站式》服务中心，琴房、小剧场、讨论室、办公室、食堂各种东西应有尽有",
                          39.950426, 116.338602),
        InterestPointData(8, "世纪钟", "逝者如斯",
                          39.950402, 116.342154),
        InterestPointData(9, "积秀园", "秀",
                          39.950394, 116.340078),
        InterestPointData(10, "南门", "全亚洲最高的校门",
                          39.94927, 116.341475),
        InterestPointData(11, "天佑会堂", "天佑，会堂",
                          39.950052, 116.340568)
};

const EdgeData defaultEdgesData[] = {
        EdgeData(0, 10, 11, 148),
        EdgeData(1, 11, 9, 119),
        EdgeData(2, 9, 7, 151),
        EdgeData(3, 9, 8, 154),
        EdgeData(4, 10, 8, 190),
        EdgeData(5, 7, 2, 173),
        EdgeData(6, 2, 11, 180),
        EdgeData(7, 2, 1, 132),
        EdgeData(8, 1, 3, 146),
        EdgeData(9, 2, 3, 211),
        EdgeData(10, 3, 4, 136),
        EdgeData(11, 4, 6, 192),
        EdgeData(12, 0, 6, 141),
        EdgeData(13, 6, 5, 42),
        EdgeData(14, 5, 0, 137),
        EdgeData(15, 9, 5, 224),
        EdgeData(16, 3, 5, 136),
        EdgeData(17, 8, 5, 234),
        EdgeData(18, 1, 8, 228),
        EdgeData(18, 8, 0, 346),
        EdgeData(19, 9, 1, 183)
};

const auto INSERT_INTEREST_POINT_DATA = QLatin1String(R"(
    insert into interest_points_data (id, name, desc, lat, lng, selected, checked) values(?, ?, ?, ?, ?, ?, ?)
    )");
const auto INSERT_EDGE_DATA = QLatin1String(R"(
    insert into edges_data (id, x, y, w) values(?, ?, ?, ?)
    )");

class Database {
public:
    static Database &getInstance() {
        static Database instance;
        return instance;
    }

    std::vector<InterestPointData> getInterestPointsData() {
        std::vector<InterestPointData> res;

        QSqlQuery query;
        query.exec("SELECT id, name, desc, lat, lng, selected, checked FROM interest_points_data");
        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString desc = query.value(2).toString();
            double lat = query.value(3).toDouble();
            double lng = query.value(4).toDouble();
            bool selected = query.value(5).toBool();
            double checked = query.value(6).toBool();
            res.emplace_back(id, name, desc, lat, lng, selected, checked);
//            qDebug() << id << name << desc << lat << lng << selected << checked;
        }

        return res;
    }

    std::vector<EdgeData> getEdgesData() {
        std::vector<EdgeData> res;

        QSqlQuery query;
        query.exec("SELECT id, x, y, w FROM edges_data");
        while (query.next()) {
            int id = query.value(0).toInt();
            int x = query.value(1).toInt();
            int y = query.value(2).toInt();
            double w = query.value(3).toDouble();
            res.emplace_back(id, x, y, w);
//            qDebug() << id << x << y << w;
        }

        return res;
    }
private:
    void insertInterestPointData(const InterestPointData &data) {
        QSqlQuery q;
        q.prepare(INSERT_INTEREST_POINT_DATA);
        q.bindValue(0, data.id);
        q.bindValue(1, data.name);
        q.bindValue(2, data.desc);
        q.bindValue(3, data.lat);
        q.bindValue(4, data.lng);
        q.bindValue(5, data.selected);
        q.bindValue(6, data.checked);
        if (!q.exec()) qDebug() << "insertInterestPointData:" << q.lastError();
    }

    void insertEdgeData(const EdgeData &data) {
        QSqlQuery q;
        q.prepare(INSERT_EDGE_DATA);
        q.bindValue(0, data.id);
        q.bindValue(1, data.x);
        q.bindValue(2, data.y);
        q.bindValue(3, data.w);
        if (!q.exec()) qDebug() << "insertEdgeData:" << q.lastError();
    }

    void initDefaultData() {
        QSqlQuery q;
        if (!q.exec("create table if not exists interest_points_data ("
                    "id integer primary key,"
                    "name text,"
                    "desc text,"
                    "lat real,"
                    "lng real,"
                    "selected int,"
                    "checked int)"))
            qDebug() << q.lastError();
        for (auto &data:defaultInterestPointsData) {
            insertInterestPointData(data);
        }

        if (!q.exec("create table if not exists edges_data ("
                    "id integer primary key,"
                    "x integer,"
                    "y integer,"
                    "w real)"))
            qDebug() << q.lastError();
        for (auto &data:defaultEdgesData) {
            insertEdgeData(data);
        }
    }

    QSqlDatabase database;

    Database() {
        qDebug() << "Initializing Database";
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("database.sqlite");
        database.open();
        initDefaultData();
//        qDebug() << res;
    }
};

#endif //BJTUGUIDE_DATABASE_H
