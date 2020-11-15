#include "game_controller.h"

GameController::~GameController() {
    std::cout << "GameController: Destructor" << std::endl;
}

void GameController::Run() {
    CheckValidityPtrs();
    sf::Event event;
    std::size_t frameCounter = 0;
    while (m_Render.lock()->window().isOpen()) {
        ++frameCounter;
        while (m_Render.lock()->window().pollEvent(event)) {
            if (m_Moved) {
                if (!m_Model.lock()->IsValidMove()) {
                    m_Model.lock()->Cancel();
                }
                m_Render.lock()->DrawAllGemStones(m_Model.lock()->GetStones());
                m_Moved = false;
                m_Rendered = true;
                continue;
            }
            if (m_Rendered && frameCounter % 8 == 0) {
                if (m_Rendered = m_Model.lock()->CheckRemovable(); m_Rendered) {
                    m_Model.lock()->DeleteElements();
                    m_Render.lock()->SetScores(m_Model.lock()->GetScores());
                }
                m_Render.lock()->DrawAllGemStones(m_Model.lock()->GetStones());
            }

            
            if (event.type == sf::Event::Closed)
                m_Render.lock()->window().close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F2) {
                    NewGame();
                    m_Rendered = true;
                }
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                MouseButton(event);
            }
        }

        // Выполняем необходимые действия по отрисовке
        m_Render.lock()->Render();
    }
}

void GameController::NewGame() {
    m_Model.lock()->NewGame();
    m_Render.lock()->SetScores(m_Model.lock()->GetScores());
    m_Render.lock()->DrawAllGemStones(m_Model.lock()->GetStones());
}

void GameController::MouseButton(sf::Event& aEvent) {
    if (aEvent.key.code == sf::Mouse::Left) {
        auto[isStone, x, y] = GetClickedElement(m_Render.lock()->GetTileSize(), m_Render.lock()->GetOffset(), aEvent.mouseButton);
        if (isStone && m_Model.lock()->SetClickedIndex(x, y)) {
            m_Render.lock()->DrawAllGemStones(m_Model.lock()->GetStones());
            m_Rendered = true;
            m_Moved = true;
            //Затребовать отрисовку смены позиций
        }
    }
}

const std::tuple<bool, int, int> GameController::GetClickedElement(
    const int aTileSize,
    const std::pair<int, int> aOffset,
    const sf::Event::MouseButtonEvent aEvent) const {
    const auto&[xOffset, yOffset] = aOffset;
    if (!IsValidClick(aTileSize, xOffset, aEvent.x))
        return { false, 0, 0 };

    if (!IsValidClick(aTileSize, yOffset, aEvent.y))
        return { false, 0, 0 };

    int xIndex = GetStoneIndex(aTileSize, xOffset, aEvent.x);
    int yIndex = GetStoneIndex(aTileSize, yOffset, aEvent.y);

    return { true, xIndex, yIndex };
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

