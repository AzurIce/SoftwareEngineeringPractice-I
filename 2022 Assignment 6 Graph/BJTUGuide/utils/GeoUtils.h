//
// Created by AzurIce on 2022/11/24.
//

#ifndef BJTUGUIDE_GEOUTILS_H
#define BJTUGUIDE_GEOUTILS_H

#include <QGeoCoordinate>
#include <utility>

const QGeoCoordinate ORIGIN = QGeoCoordinate(39.953971, 116.336953);
const double C = 255.0 / 237.14;

class GeoUtils {
public:
    static double getDisY(const QGeoCoordinate &coord1, const QGeoCoordinate &coord2) {
        QGeoCoordinate m(coord1.latitude(), coord2.longitude());
        return coord2.distanceTo(m);
    }

    static double getDisX(const QGeoCoordinate &coord1, const QGeoCoordinate &coord2) {
        QGeoCoordinate m(coord1.latitude(), coord2.longitude());
        return coord1.distanceTo(m);
    }

    static std::pair<double, double> getCoord(const QGeoCoordinate &p, const QGeoCoordinate &origin = ORIGIN) {
        return std::make_pair(C * getDisX(p, origin), C * getDisY(p, origin));
    }

    static std::pair<double, double> getCoord(double lat, double lng) {
        return getCoord(QGeoCoordinate(lat, lng));
    }
};

#endif //BJTUGUIDE_GEOUTILS_H
