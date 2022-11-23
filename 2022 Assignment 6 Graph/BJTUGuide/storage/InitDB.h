//
// Created by AzurIce on 2022/11/23.
//

#ifndef BJTUGUIDE_INITDB_H
#define BJTUGUIDE_INITDB_H

#include <QtSql>

// insert into point (name, text, image_id, enabled, rank) values(?, ?, ?, ?, ?)
void addPoint(QSqlQuery &q, const QString &name, const QString &desc,  const int &image_id, const bool &enabled,
             const int &rank)
{
    q.addBindValue(name);
    q.addBindValue(desc);
    q.addBindValue(image_id);
    q.addBindValue(enabled);
    q.addBindValue(rank);
    q.exec();
}

// insert into image (filename, img_data) values(?, ?)
QVariant addImage(QSqlQuery &q, const QString &filename, const QByteArray img_data)
{
    q.addBindValue(filename);
    q.addBindValue(img_data);
    q.exec();
    return q.lastInsertId();
}

const auto POINT_SQL = QLatin1String(R"(
    create table if not exists point (id integer primary key, name text, desc text, image_id integer, enabled integer, rank integer)
    )");

const auto IMAGE_SQL =  QLatin1String(R"(
    create table if not exists image (id integer primary key, filename text, img_data blob)
    )");

const auto INSERT_POINT_SQL = QLatin1String(R"(
    insert into point (name, desc text, image_id, enabled, rank) values(?, ?, ?, ?, ?)
    )");

const auto INSERT_IMAGE_SQL = QLatin1String(R"(
    insert into image (filename, img_data) values(?, ?)
    )");


void insertDefaultData() {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery q;

    QPixmap pixmap = QPixmap(":/res/YiFu.png");
    QByteArray inByteArray;
    QBuffer inBuffer(&inByteArray);
    inBuffer.open(QIODevice::WriteOnly);
    pixmap.save(&inBuffer, "PNG");

    q.prepare(INSERT_IMAGE_SQL);
    QVariant imageYiFuId = addImage(q, "YiFu", inByteArray);

    q.prepare(INSERT_POINT_SQL);
    QVariant asimovId = addPoint(q, QLatin1String("逸夫楼"), QDate(1920, 2, 1));
//    QVariant greeneId = addAuthor(q, QLatin1String("Graham Greene"), QDate(1904, 10, 2));
//    QVariant pratchettId = addAuthor(q, QLatin1String("Terry Pratchett"), QDate(1948, 4, 28));

//    if (!q.prepare(INSERT_IMAGE_SQL))
//        return q.lastError();
//    QVariant sfiction = addGenre(q, QLatin1String("Science Fiction"));
//    QVariant fiction = addGenre(q, QLatin1String("Fiction"));
//    QVariant fantasy = addGenre(q, QLatin1String("Fantasy"));

//    if (!q.prepare(INSERT_BOOK_SQL))
//        return q.lastError();
//    addBook(q, QLatin1String("Foundation"), 1951, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("Foundation and Empire"), 1952, asimovId, sfiction, 4);
//    addBook(q, QLatin1String("Second Foundation"), 1953, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("Foundation's Edge"), 1982, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("Foundation and Earth"), 1986, asimovId, sfiction, 4);
//    addBook(q, QLatin1String("Prelude to Foundation"), 1988, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("Forward the Foundation"), 1993, asimovId, sfiction, 3);
//    addBook(q, QLatin1String("The Power and the Glory"), 1940, greeneId, fiction, 4);
//    addBook(q, QLatin1String("The Third Man"), 1950, greeneId, fiction, 5);
//    addBook(q, QLatin1String("Our Man in Havana"), 1958, greeneId, fiction, 4);
//    addBook(q, QLatin1String("Guards! Guards!"), 1989, pratchettId, fantasy, 3);
//    addBook(q, QLatin1String("Night Watch"), 2002, pratchettId, fantasy, 3);
//    addBook(q, QLatin1String("Going Postal"), 2004, pratchettId, fantasy, 3);
}

void initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.open();

    QSqlQuery q;
    q.exec(POINT_SQL);
    q.exec(IMAGE_SQL);
}

#endif //BJTUGUIDE_INITDB_H
