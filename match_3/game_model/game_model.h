#pragma once
#include "assets/assets.h"
#include "gem_stone.h"   
#include <iostream>
#include <boost/format.hpp>
#include <set>
class GameModel {
    struct Position {
        int x = 0;
        int y = 0;
        bool operator<(const Position& aRhs) const {
            return std::tie(x, y) < std::tie(aRhs.x, aRhs.y);
        }
    };

    stones::gem_stones_t m_GemStones;
    mutable std::size_t m_Scores = 0;
    std::tuple<bool, Position>     m_Clicked{ false, {0, 0 }};
    std::tuple<Position, Position> m_LastMove{ {0, 0}, {0, 0} };
    mutable std::set<Position> m_RemovableElements;

public:
    GameModel();
    ~GameModel();
    const stones::gem_stones_t& GetStones() const;
    bool SetClickedIndex(const int aX, const int aY);
    void Cancel();
    bool IsValidMove() const;
    std::size_t GetScores() const;
    void NewGame();
    void DeleteElements();
    bool CheckRemovable();
    //bool Deletable();
private:
    void Init();
    GemsType RandomType() const;
    void SwapStone(GemStone& aStone1, GemStone& aStone2);
    //Match 3 Line
    bool IsMatch(const int aX, const int aY) const;
    bool IsMatchRow(const int aX, const int aY) const;
    bool IsMatchColumn(const int aX, const int aY) const;
    bool IsMatch3InRow(const int aX, const int aY) const;
    bool IsMatch3InColumn(const int aX, const int aY) const;
    bool CheckMatch3Line(const Position&& aGem1, const Position&& aGem2, const Position&& aGem3) const;
    void DeleteElement(Position aPos);
    bool IsMatch_old(const int aX, const int aY) const;
};