//
// Created by AzurIce on 2022/11/23.
//

#ifndef BJTUGUIDE_INTERESTPOINTDATA_H
#define BJTUGUIDE_INTERESTPOINTDATA_H

#include <QString>

class InterestPointData {
public:
    InterestPointData(const int &id, QString name, QString desc,
                      const double &lat, const double &lng,
                      const bool &selected = false, const bool &checked = true) :
            id(id), name(std::move(name)), desc(std::move(desc)),
            lat(lat), lng(lng),
            selected(selected), checked(checked) {}

    int id;
    QString name;
    QString desc;
    double lng;
    double lat;
    bool selected;
    bool checked;
};


#endif //BJTUGUIDE_INTERESTPOINTDATA_H
