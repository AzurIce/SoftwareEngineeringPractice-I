//
// Created by AzurIce on 2022/11/23.
//

#ifndef BJTUGUIDE_DATABASE_H
#define BJTUGUIDE_DATABASE_H

#include <QSqlDatabase>

class Database {
private:
    QSqlDatabase database;
    Database() {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.open();
    }
    ~Database();
public:
    static Database& getInstance() {
        static Database instance;
        return instance;
    }
};
#endif //BJTUGUIDE_DATABASE_H
