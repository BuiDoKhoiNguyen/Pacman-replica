
#ifndef _MP_H_
#define _MP_H_

#include "../Manager/LogStatus.h"
#include <fstream>
#include <iostream>
#include <algorithm>


class Mp
{
private:
    static const int MAP_WIDTH = 28;
    static const int MAP_HEIGHT = 31;
    const std::string mapFile = "Source/Map/map.txt";

    LogStatus* Console = new LogStatus("Map");
public:
    Mp();
    ~Mp();
};


