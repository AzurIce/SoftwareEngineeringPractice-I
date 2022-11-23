//
// Created by AzurIce on 2022/11/23.
//

#ifndef BJTUGUIDE_INTERESTPOINTLIST_H
#define BJTUGUIDE_INTERESTPOINTLIST_H

#include "InterestPoint.h"
#include <vector>

class InterestPointList {
public:
    InterestPointList() = default;

    std::vector<bool> checked = std::vector<bool>(4, true);

    std::vector<InterestPoint> interestPoints{
        InterestPoint(0, "逸夫教学楼", "软件学院", QPixmap(":res/YiFu.png"), 116.344720, 39.951676),
        InterestPoint(1, "思源楼", "思源", QPixmap(":res/YiFu.png"), 116.340831, 39.951491),
        InterestPoint(2, "思源西楼", "法学院", QPixmap(":res/YiFu.png"), 116.339892, 39.951261),
        InterestPoint(3, "思源东楼", "经管学院", QPixmap(":res/YiFu.png"), 116.341791, 39.951577),
        InterestPoint(4, "明湖", "就，湖", QPixmap(":res/YiFu.png"), 116.342272,39.952038),
        InterestPoint(5, "芳华园", "花花草草木木", QPixmap(":res/YiFu.png"), 116.343216,39.951512),
        InterestPoint(6, "图书馆", "书书书书书书书", QPixmap(":res/YiFu.png"), 116.343409,39.952006),
        InterestPoint(7, "学活", "《一站式》服务中心", QPixmap(":res/YiFu.png"), 116.338602,39.950426),
        InterestPoint(8, "世纪钟", "逝者如斯", QPixmap(":res/YiFu.png"), 116.342154, 39.950402),
        InterestPoint(9, "积秀园", "秀", QPixmap(":res/YiFu.png"), 116.340078,39.950394),
    };
};


#endif //BJTUGUIDE_INTERESTPOINTLIST_H
