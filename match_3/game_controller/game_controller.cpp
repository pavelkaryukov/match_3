#include "game_controller.h"

GameController::~GameController() {
    std::cout << "GameController: Destructor" << std::endl;
}

void GameController::Run() {
    CheckValidityPtrs();
    sf::Event event;
    std::size_t counter = 0;
    while (m_Render.lock()->window().isOpen()) {
        while (m_Render.lock()->window().pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                m_Render.lock()->window().close();

            if (event.type == sf::Event::KeyPressed) {
                ++counter;
                m_Render.lock()->SetScores(counter);
            }
        }

        // Выполняем необходимые действия по отрисовке
        m_Render.lock()->Render();
    }
}

void GameController::CheckValidityPtrs() {
    if (m_Render.expired())
        throw std::runtime_error("GameController: m_Render is empty");
    if (m_Model.expired())
        throw std::runtime_error("GameController: m_Model is empty");
}

