#pragma once

enum class GemsType {
    Type1 = 0,
    Type2,
    Type3,
    Type4,
    Type5,
    Type6,
    Type7
};

struct GemStone {
    //int X        ;//Координаты общие
    //int Y        ;//Координаты общие
    //int Alpha    ;//видимость
    GemsType Type;//тип камня
    int Row;//индекс в поле строка
    int Column;//индекс в поле столбец

    //methods
    GemStone() {};
    GemStone(const int aRow, const int aColumn, const GemsType aType) : Row(aRow), Column(aColumn), Type(aType) {};
    ~GemStone() {};// { std::cout << "Gemstone: destructor" << std::endl; }
};
