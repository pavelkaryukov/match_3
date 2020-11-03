#pragma once
#include "assets/assets.h"
#include "gem_stone.h"
#include <array>           
#include <iostream>
#include <boost/format.hpp>

class GameModel {
    static const int ELEMENTS_NUM = 8;
    using gem_stones_t = std::array<std::array<GemStone, ELEMENTS_NUM>, ELEMENTS_NUM>;
    gem_stones_t m_GemStones;
public:
    GameModel();
    ~GameModel();
    const gem_stones_t& GetStones() const;
private:
    void Init();
    GemsType RandomType() const;
};