#pragma once
#include <SFML/Graphics.hpp>

class GameRender : public sf::Drawable, public sf::Transformable {
    sf::RenderWindow m_Window;
    sf::Text m_Text;
public:
    GameRender();
    ~GameRender() {};
    sf::RenderWindow& window() { return m_Window; };
    bool Init();
    void Render();
    void ChangeText(std::string&& aStr);
    void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const override;
private:
};
