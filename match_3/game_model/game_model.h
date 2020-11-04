#pragma once
#include "assets/assets.h"
#include "gem_stone.h"   
#include <iostream>
#include <boost/format.hpp>

class GameModel {
    stones::gem_stones_t m_GemStones;
public:
    GameModel();
    ~GameModel();
    const stones::gem_stones_t& GetStones() const;
    bool SetClickedIndex(const int aX, const int aY);
private:
    std::tuple<bool, int, int> m_Clicked;
    void Init();
    GemsType RandomType() const;
    void SwapStone(GemStone& aStone1, GemStone& aStone2);
};