#include "game_model.h" 

GameModel::GameModel() {
    Init();
}

GameModel::~GameModel() {
    std::cout << "GameModel: Destructor" << std::endl;
}

const stones::gem_stones_t& GameModel::GetStones() const {
    return m_GemStones;
}

bool GameModel::SetClickedIndex(const int aX, const int aY) {    
    if (auto& [clicked, x, y] = m_Clicked; !clicked) {
        clicked = true;
        x = aX;
        y = aY;
        return false;
    }
    else {
        int distance = std::abs(aX - x) + std::abs(aY - y);
        if (distance == 1) {
            SwapStone(m_GemStones[x][y], m_GemStones[aX][aY]);
            m_Clicked = { false, 0, 0 };
            return true;
        }
        else {
            m_Clicked = { true, aX, aY };
            return false;
        }
    }
    return false;
}

void GameModel::Init() {
    for (int i = 0; i < m_GemStones.size(); ++i) {
        for (int j = 0; j < m_GemStones[i].size(); ++j) {
            m_GemStones[i][j] = GemStone(i, j, RandomType());
        }
    }
}

GemsType GameModel::RandomType() const {
    return static_cast<GemsType>(rand() % (static_cast<std::uint32_t>(GemsType::Type7) + 1));
}

void GameModel::SwapStone(GemStone& aStone1, GemStone& aStone2) {
    std::swap(aStone1, aStone2);
}
