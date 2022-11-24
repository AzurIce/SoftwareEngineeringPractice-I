//
// Created by AzurIce on 2022/11/25.
//

#ifndef BJTUGUIDE_EDGEDATA_H
#define BJTUGUIDE_EDGEDATA_H


class EdgeData {
public:
    EdgeData(int id, int x, int y, int w): id(id), x(x), y(y), w(w) {}

    int id;
    int x;
    int y;
    double w;
};


#endif //BJTUGUIDE_EDGEDATA_H
