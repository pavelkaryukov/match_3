#pragma once
#include <SFML/Graphics.hpp>

class IGameRender : public sf::Drawable, public sf::Transformable {
public:
    virtual sf::RenderWindow& window() = 0;
    virtual bool Init()   = 0;
    virtual void Render() = 0;
    virtual void SetScores(std::size_t aScore) = 0;//to igame //¬ынести в приват, очки будет присылать GameModel
    virtual ~IGameRender() {};
protected:
    virtual void draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const = 0;
};
