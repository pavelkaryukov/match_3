#include "game_render.h"
#include "assets/assets.h"
#include <boost/format.hpp>

GameRender::GameRender(std::weak_ptr<GameModel>&& aModel) : m_Model(std::move(aModel)) {
    Init();
}

GameRender::~GameRender() {
    std::cout << "GameRender: Destructor" << std::endl;
}

namespace windows_size {
    static const int RENDER_X = 740;
    static const int RENDER_Y = 480;
    static const int FIELD_X = 430;
    static const int FIELD_Y = 430;
}

bool GameRender::Init() {
    // Создаем окно размером 600 на 600 и частотой обновления 60 кадров в секунду
    m_Window.create(sf::VideoMode(windows_size::RENDER_X, windows_size::RENDER_Y), "Match-3 Line Game");
    m_Window.setFramerateLimit(60);
    // Текст с обозначением клавиш
    m_Text = sf::Text("F2 - New Game / Esc - Exit / Left Mouse Button - Move Gem", Assets::Instance().GetFont(), 20);
    m_Text.setFillColor(sf::Color::Red);
    m_Text.setPosition(40.f, 0.f);
    
    m_ScoresText = sf::Text("", Assets::Instance().GetFont(), 50);
    SetScores(0);
    m_ScoresText.setFillColor(sf::Color::Red);
    m_ScoresText.setPosition(480.f, 405.f);
    return true;
}

void GameRender::Render() {
    m_Window.clear();
    m_Window.draw(*this);
    m_Window.draw(m_Text);
    m_Window.draw(m_ScoresText);
    m_Window.display();
}

void GameRender::draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const {
    aStates.transform *= getTransform();
    sf::Color color = sf::Color(100, 100, 200);
    sf::Sprite background(Assets::Instance().GetBackGround());
    background.setPosition(0.f, 0.f);
    aTarget.draw(background, aStates);
    // Рисуем рамку игрового поля
    sf::RectangleShape shape(sf::Vector2f(windows_size::FIELD_X, windows_size::FIELD_Y));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(45, 25);//Сместили позицию для второго текста
    aTarget.draw(shape, aStates);
    DrawAllGemStones();
}

void GameRender::SetScores(std::size_t aScore) {
    m_ScoresText.setString(boost::str(boost::format("Scores:%1%")%aScore));
}

void GameRender::DrawAllGemStones() const {
    CheckValidityPtr();
    auto model = m_Model.lock();
    for (auto& row : model->GetStones()) {
        for (auto& stone : row) {
            DrawGemStone(stone);
        }
    }
}

void GameRender::CheckValidityPtr() const {
    if (m_Model.expired())
        throw std::runtime_error("GameRender: m_GameModel are expired");
}

void GameRender::DrawGemStone(const GemStone& aStone) const {

}
