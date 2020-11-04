#pragma once
//#include "igame_render.h"
#include "game_model/gem_stone.h"
#include <SFML/Graphics.hpp>
struct SpriteAction{
    int  MoveX = 0;
    int  MoveY = 0;
    int  Visibiliti = 255;
    bool Alive = true;
};

//TODO:: Сделать интерфейс с комоторым будет работать контроллер
class GameRender : public sf::Drawable, public sf::Transformable {//public IGameRender {// public sf::Drawable, public sf::Transformable{
    static const int   RENDER_X = 740;
    static const int   RENDER_Y = 480;
    static const int   FIELD_X = 430;
    static const int   FIELD_Y = 430;
    static const int   TILE_SIZE = 54; 
    static const int   SPRITE_CUT_OFFSET = 49;
    const sf::Vector2i STONE_OFFSET{ 48, 24 };

    sf::RenderWindow m_Window;
    std::vector<std::pair<sf::Sprite, SpriteAction>> m_SpriteStones;//Доступ к спрайтам по линейному индексу
    sf::Text m_Text;
    sf::Text m_ScoresText;
public:
    GameRender();
    ~GameRender();
    sf::RenderWindow& window() { return m_Window; };
    bool Init() ;
    void Render();
    void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;
    void SetScores(std::size_t aScore);
    void DrawAllGemStones(const stones::gem_stones_t& aStones);
    void MoveSprites();
    const int GetTileSize() const { return TILE_SIZE; };
    const std::pair<int, int> GetOffset() const { return { STONE_OFFSET.x, STONE_OFFSET.y }; };
private:
    void _MoveSprites(); //rename
    void DrawGemStone(const GemStone& aStone, const int aX, const int aY) ;
    sf::IntRect GetStoneTileField(const GemsType& aType) const;
};
