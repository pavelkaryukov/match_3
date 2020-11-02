#pragma once
#include "game_render/game_render.h"
#include "game_model/game_model.h"
#include <SFML/Graphics.hpp>

//TODO:: переделать на shared_ptr
class GameController {
    std::weak_ptr<GameRender> m_Render;
    std::weak_ptr<GameModel>  m_Model;
public:
    GameController(std::weak_ptr<GameRender>&& aRender, std::weak_ptr<GameModel>&& aModel) : m_Render(std::move(aRender)) , m_Model(std::move(aModel)) {};
    ~GameController();
    void Run();
private:
    void CheckValidityPtrs();
};