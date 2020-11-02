#include "game_render.h"
#include "assets/assets.h"
#include <boost/format.hpp>

GameRender::GameRender(std::weak_ptr<GameModel>&& aModel) : m_Model(std::move(aModel)) {
    Init();
}

GameRender::~GameRender() {
    std::cout << "GameRender: Destructor" << std::endl;
}

bool GameRender::Init() {
    m_Window.create(sf::VideoMode(RENDER_X, RENDER_Y), "Match-3 Line Game");
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
    sf::RectangleShape shape(sf::Vector2f(FIELD_X, FIELD_Y));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(45, 25);//Сместили позицию для второго текста
    aTarget.draw(shape, aStates);
    //Отрисовка камней
    DrawAllGemStones(aTarget,aStates);
}

void GameRender::SetScores(std::size_t aScore) {
    m_ScoresText.setString(boost::str(boost::format("Scores:%1%")%aScore));
}

void GameRender::DrawAllGemStones(sf::RenderTarget& aTarget, sf::RenderStates& aStates) const
{
    CheckValidityPtr();
    auto model = m_Model.lock();
    for (auto& row : model->GetStones()) {
        for (auto& stone : row) {
            DrawGemStone(stone, aTarget, aStates);
        }
    }
}

void GameRender::CheckValidityPtr() const {
    if (m_Model.expired())
        throw std::runtime_error("GameRender: m_GameModel are expired");
}

void GameRender::DrawGemStone(const GemStone& aStone, sf::RenderTarget& aTarget, sf::RenderStates& aStates) const {
    sf::Sprite sprite{ Assets::Instance().GetGems() };//TODO::Вынести за цикл?
    sprite.setTextureRect(GetStoneTileField(aStone.Type));
    sprite.setColor(sf::Color(255, 255, 255, 255));
    sprite.setPosition(STONE_OFFSET.x + TILE_SIZE * aStone.Row , STONE_OFFSET.y + TILE_SIZE * aStone.Column );
    aTarget.draw(sprite, aStates);                                
}

sf::IntRect GameRender::GetStoneTileField(const GemsType& aType) const {
    return sf::IntRect((static_cast<int>(aType)) * SPRITE_CUT_OFFSET, 0, SPRITE_CUT_OFFSET, SPRITE_CUT_OFFSET);
}
