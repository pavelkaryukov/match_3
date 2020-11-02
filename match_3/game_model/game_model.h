#pragma once
#include "assets/assets.h"
#include <array>           
#include <iostream>
#include <boost/format.hpp>

enum class GemsType {
    Type1 = 0,
    Type2,
    Type3,
    Type4,
    Type5,
    Type6,
    Type7
};

//TODO::В отдельный хедр
struct GemStone {
    //int X        ;//Координаты общие
    //int Y        ;//Координаты общие
    //int Alpha    ;//видимость
    GemsType Type;//тип камня
    int Row   ;//индекс в поле строка
    int Column;//индекс в поле столбец
    //methods

    GemStone() {};
    GemStone(const int aRow, const int aColumn, const GemsType aType) : Row(aRow), Column(aColumn), Type(aType){};
    ~GemStone() {};// { std::cout << "Gemstone: destructor" << std::endl; }
};

class GameModel {
public:
    static const int gElemenetsNum = 8;
private:
    using gem_stones_t = std::array<std::array<GemStone, gElemenetsNum>, gElemenetsNum>;
    gem_stones_t m_GemStones;// [gElemenetsNum][gElemenetsNum];
public:
    GameModel();
    ~GameModel();
    const gem_stones_t& GetStones() const;
private:
    void Init();
    GemsType RandomType() const;
};