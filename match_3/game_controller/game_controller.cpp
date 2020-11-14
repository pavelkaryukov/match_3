#include "game_controller.h"

GameController::~GameController() {
    std::cout << "GameController: Destructor" << std::endl;
}

void GameController::Run() {
    CheckValidityPtrs();
    sf::Event event;
    std::size_t frameCounter = 0;
    bool firstStart = true, moved = false;
    while (m_Render.lock()->window().isOpen()) {
        if (moved && ((++frameCounter) % 16 == 0)) {
            if (m_Model.lock()->IsValidMove()) {
                //Positive move - destroy line
            }
            else {
                m_Model.lock()->Cancel();
            }
            m_Render.lock()->DrawAllGemStones(m_Model.lock()->GetStones());
            moved = false;
        }

        if (firstStart) {
            m_Render.lock()->DrawAllGemStones(m_Model.lock()->GetStones());
            firstStart = false;
        }
        while (m_Render.lock()->window().pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                m_Render.lock()->window().close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F2) {
                    m_Model.lock()->NewGame();
                    m_Render.lock()->SetScores(m_Model.lock()->GetScores());
                    m_Render.lock()->DrawAllGemStones(m_Model.lock()->GetStones());
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    auto [isStone, x, y] = GetClickedElement(m_Render.lock()->GetTileSize(), m_Render.lock()->GetOffset(), event.mouseButton);
                    if (isStone && m_Model.lock()->SetClickedIndex(x, y)) {
                        m_Render.lock()->DrawAllGemStones(m_Model.lock()->GetStones());
                        moved = true;
                        frameCounter = 1;
                        //Затребовать отрисовку смены позиций
                        int stop1 = 0;
                    }
                }
                int stop1 = 0;
            }

        }

        // Выполняем необходимые действия по отрисовке
        m_Render.lock()->Render();
    }
}

const std::tuple<bool, int, int> GameController::GetClickedElement (
    const int aTileSize, 
    const std::pair<int, int> aOffset, 
    const sf::Event::MouseButtonEvent aEvent) const
{
    const auto& [xOffset, yOffset] = aOffset;
    if (!IsValidClick(aTileSize, xOffset, aEvent.x))
        return { false, 0, 0 };

    if (!IsValidClick(aTileSize, yOffset, aEvent.y))
        return { false, 0, 0 };
    
    int xIndex = GetStoneIndex(aTileSize, xOffset, aEvent.x);
    int yIndex = GetStoneIndex(aTileSize, yOffset, aEvent.y);

    return { true, xIndex, yIndex};
}

bool GameController::IsValidClick(const int aTileSize, const int aOffset, const int aPos) const {
    if (aPos < aOffset || aPos > aOffset + aTileSize * 8)//уйти от литералов
        return false;
}

int GameController::GetStoneIndex(const int aTileSize, const int aOffset, const int aPos) const {
    return (aPos - aOffset) / aTileSize;
}

void GameController::CheckValidityPtrs() {
    if (m_Render.expired())
        throw std::runtime_error("GameController: m_Render is empty");
    if (m_Model.expired())
        throw std::runtime_error("GameController: m_Model is empty");
}

