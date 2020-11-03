#pragma once
#include "igame_render.h"
#include "game_model/game_model.h" 

//TODO:: Сделать интерфейс с комоторым будет работать контроллер
class GameRender : public IGameRender {// public sf::Drawable, public sf::Transformable{
    static const int   RENDER_X = 740;
    static const int   RENDER_Y = 480;
    static const int   FIELD_X = 430;
    static const int   FIELD_Y = 430;
    static const int   TILE_SIZE = 54; 
    static const int   SPRITE_CUT_OFFSET = 49;
    const sf::Vector2i STONE_OFFSET{ 48, 24 };

    std::weak_ptr<GameModel> m_Model;
    sf::RenderWindow m_Window;
    sf::Text m_Text;
    sf::Text m_ScoresText;
public:
    GameRender(std::weak_ptr<GameModel>&& aModel);
    ~GameRender();
    sf::RenderWindow& window() override { return m_Window; };
    bool Init() override;
    void Render() override;
    void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;
    void SetScores(std::size_t aScore) override;
private:
    void DrawAllGemStones(sf::RenderTarget& aTarget, sf::RenderStates& aStates) const;
    void CheckValidityPtr() const;
    void DrawGemStone(const GemStone& aStone, sf::RenderTarget& aTarget, sf::RenderStates& aStates) const;
    sf::IntRect GetStoneTileField(const GemsType& aType) const;
};
