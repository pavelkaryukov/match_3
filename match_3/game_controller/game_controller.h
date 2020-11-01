#pragma once
#include "../game_render/game_render.h"
#include <SFML/Graphics.hpp>

class GameController {
    std::weak_ptr<GameRender> m_Render;
public:
    GameController(std::weak_ptr<GameRender>&& aRender) : m_Render(std::move(aRender)) {};
    ~GameController() {};
    void Run();
};