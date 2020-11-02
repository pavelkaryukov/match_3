#include "game_model.h" 

GameModel::GameModel() {
    Init();
}

GameModel::~GameModel() {
    std::cout << "GameModel: Destructor" << std::endl;
}

const GameModel::gem_stones_t& GameModel::GetStones() const {
    return m_GemStones;
}

void GameModel::Init() {
    for (int i = 0; i < gElemenetsNum; ++i) {
        for (int j = 0; j < gElemenetsNum; ++j) {
            m_GemStones[i][j] = GemStone(i, j, RandomType());
        }
    }
}

GemsType GameModel::RandomType() const {
    return static_cast<GemsType>(rand() % (static_cast<std::uint32_t>(GemsType::Type7) + 1));
}
