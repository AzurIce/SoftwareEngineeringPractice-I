//
// Created by AzurIce on 2022/11/23.
//

#ifndef BJTUGUIDE_INTERESTPOINT_H
#define BJTUGUIDE_INTERESTPOINT_H

#include <QString>
#include <QPixmap>
#include <QObject>
#include <utility>

class InterestPoint/* : public QObject*/ {
//Q_OBJECT
//
//    Q_PROPERTY(QString name READ name)
//    Q_PROPERTY(QString desc READ desc)
//    Q_PROPERTY(QPixmap image READ image)
//    Q_PROPERTY(double lng READ lng)
//    Q_PROPERTY(double lat READ lat)
public:
    InterestPoint() = default;

    InterestPoint(const int &id, const QString &name, const QString &desc, const QPixmap &image,
                  const double &lng, const double &lat) :
            m_id(id), m_name(name), m_desc(desc), m_image(image),
            m_lng(lng), m_lat(lat) {}

    int id() {
        return m_id;
    }

    QString name() {
        return m_name;
    }

    QString desc() {
        return m_desc;
    }

    QPixmap image() {
        return m_image;
    }

    [[nodiscard]] double lng() const {
        return m_lng;
    }

    [[nodiscard]] double lat() const {
        return m_lat;
    }

private:
    int m_id;
    QString m_name;
    QString m_desc;
    QPixmap m_image;
    double m_lng;
    double m_lat;
};


#endif //BJTUGUIDE_INTERESTPOINT_H
