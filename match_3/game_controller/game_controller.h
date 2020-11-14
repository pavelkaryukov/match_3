#pragma once
#include "game_render/game_render.h"
#include "game_model/game_model.h"
#include <SFML/Graphics.hpp>

class GameController {
    std::weak_ptr<GameRender> m_Render;
    std::weak_ptr<GameModel>  m_Model;

public:
    GameController(
        std::weak_ptr<GameRender>&& aRender, 
        std::weak_ptr<GameModel>&& aModel
    ) :  m_Render(std::move(aRender)) , m_Model(std::move(aModel)) {};

    ~GameController();
    void Run();

private:
    const std::tuple<bool, int, int> GetClickedElement(const int aTileSize, const std::pair<int, int> aOffset, const sf::Event::MouseButtonEvent aEvent) const;
    bool IsValidClick(const int aTileSize, const int aOffset, const int aPos) const;
    int  GetStoneIndex    (const int aTileSize, const int aOffset, const int aPos) const;
    void CheckValidityPtrs();
};