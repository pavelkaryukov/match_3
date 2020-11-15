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
    if (auto& [clicked, pos] = m_Clicked; !clicked) {
        clicked = true;
        pos.x = aX;
        pos.y = aY;
        return false;
    }
    else {
        int distance = std::abs(aX - pos.x) + std::abs(aY - pos.y);
        if (distance == 1) {
            SwapStone(m_GemStones[pos.x][pos.y], m_GemStones[aX][aY]);
            m_LastMove = { pos,  { aX, aY } };
            m_Clicked = { false, {0, 0} };
            return true;
        }
        else {
            m_Clicked = { false, {0, 0} };//{ true, aX, aY };
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


bool GameModel::IsMatch(const int aX, const int aY) const {
    for (int i = 0; i < m_GemStones.size(); ++i)
        IsMatchRow(i, aY);

    for (int j = 0; j < m_GemStones.size(); ++j)
        IsMatch3InColumn(aX, j);
    return !m_RemovableElements.empty();
}

bool GameModel::IsMatch_old(const int aX, const int aY) const {
    return IsMatchRow(aX, aY) || IsMatch3InColumn(aX, aY);
}

bool GameModel::IsMatchRow(const int aX, const int aY) const {
    const int leftBorder = aX == 0 || aX == 1 ? 0 : aX - 2;
    const int rightBorder = (aX + 1 == m_GemStones.size()) || (aX + 2 == m_GemStones.size()) ? m_GemStones.size() - 1 : aX + 2;
    bool res = false;
    for (int i = leftBorder; i < rightBorder; ++i) {
        res = res || IsMatch3InRow(i, aY);
    }
    return res;
}

bool GameModel::IsMatchColumn(const int aX, const int aY) const {
    const int bottomBorder = aY == 0 || aY == 1 ? 0 : aY - 2;
    const int topBorder = (aY + 1 == m_GemStones.size()) || (aY + 2 == m_GemStones.size()) ? m_GemStones.size() - 1 : aY + 2;
    bool res = false;
    for (int i = bottomBorder; i < topBorder; ++i) {
        res = res || IsMatch3InColumn(i, aY);
    }
    return res;
}

bool GameModel::IsMatch3InRow(const int aX, const int aY) const {
    if (aX != 0 && aX + 1 != m_GemStones.size()) {
        return CheckMatch3Line({ aX - 1, aY }, { aX, aY }, { aX + 1, aY });
    }
    else if (aX == 0) {                                             
        return CheckMatch3Line({ aX, aY }, { aX + 1, aY }, { aX + 2, aY });
    }
    else if (aX + 1 == m_GemStones.size()) {
        return CheckMatch3Line({ aX - 2, aY }, { aX - 1, aY }, { aX, aY });
    }
}

bool GameModel::IsMatch3InColumn(const int aX, const int aY) const {
    if (aY != 0 && aY + 1 != m_GemStones[0].size()) { 
        return CheckMatch3Line({ aX, aY - 1 }, { aX, aY }, {aX, aY + 1});
    }
    else if (aY == 0) {                                           
        return CheckMatch3Line({ aX, aY }, { aX, aY + 1 }, { aX, aY + 2 });
    }
    else if (aY + 1 == m_GemStones[0].size()) { 
        return CheckMatch3Line({ aX, aY - 2}, { aX, aY - 1 }, { aX, aY});
    }
}

bool GameModel::CheckMatch3Line(const Position&& aGem1, const Position&& aGem2, const Position&& aGem3) const {
    bool res = m_GemStones[aGem1.x][aGem1.y].Type == m_GemStones[aGem2.x][aGem2.y].Type && m_GemStones[aGem2.x][aGem2.y].Type == m_GemStones[aGem3.x][aGem3.y].Type;
    if (res) {
        m_RemovableElements.insert(aGem1);
        m_RemovableElements.insert(aGem2);
        m_RemovableElements.insert(aGem3);
    }
    return res;
}

void GameModel::DeleteElement(Position aPos) {
    const int lastY = 0;
    for (int posY = aPos.y; posY > lastY; --posY) {
        m_GemStones[aPos.x][posY] = std::move(m_GemStones[aPos.x][posY - 1]);
    }
    m_GemStones[aPos.x][0] = GemStone(aPos.x, lastY, RandomType());
}

void GameModel::Cancel() {
    auto&[pos1, pos2] = m_LastMove;
    SwapStone(m_GemStones[pos1.x][pos1.y], m_GemStones[pos2.x][pos2.y]);
    m_LastMove = {};
}

bool GameModel::IsValidMove() const {
    m_RemovableElements.clear();
    auto&[pos1, pos2] = m_LastMove;
    bool res1 = IsMatch(pos1.x, pos1.y);
    bool res2 = IsMatch(pos2.x, pos2.y);
    return res1 || res2;
}

std::size_t GameModel::GetScores() const {
    return m_Scores;
}

void GameModel::NewGame() {
    m_Scores = 0;
    m_Clicked = { false, {0, 0} };
    m_LastMove = { {0, 0}, {0, 0} };
    Init();
}

void GameModel::DeleteElements() {
    m_Scores += m_RemovableElements.size();
    for (auto& elem : m_RemovableElements) {
        DeleteElement(elem);
    }
    m_RemovableElements.clear();
}

bool GameModel::CheckRemovable() {
    for (int i =0; i < m_GemStones.size(); ++i)
        for (int j = 0; j < m_GemStones[i].size(); ++j) 
            IsMatch(i, j);
    return !m_RemovableElements.empty();
}
