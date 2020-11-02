#pragma once
#include "game_model/game_model.h" 
#include <SFML/Graphics.hpp>


class GameRender : public sf::Drawable, public sf::Transformable {
    std::weak_ptr<GameModel> m_Model;
    sf::RenderWindow m_Window;
    sf::Text m_Text;
    sf::Text m_ScoresText;
public:
    GameRender(std::weak_ptr<GameModel>&& aModel);
    ~GameRender();
    sf::RenderWindow& window() { return m_Window; };
    bool Init();
    void Render();
    void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;
    void SetScores(std::size_t aScore);//¬ынести в приват, очки будет присылать GameModel
private:
    void DrawAllGemStones() const;
    void CheckValidityPtr() const;
    void DrawGemStone(const GemStone& aStone) const;
};
