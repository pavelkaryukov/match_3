#include "game_controller/game_controller.h"
#include "game_model/game_model.h"
#include "game_render/game_render.h"
#include <iostream>

void Run() {
    std::shared_ptr<GameModel>  model = std::make_shared<GameModel>();	// Создаем игровую модель
    std::shared_ptr<GameRender> render = std::make_shared<GameRender>(/*model*/);	// Создаем представление
    GameController controller(render, model);	// Создаем контроллер
    try {
        controller.Run(); // Запускаем игру
    }
    catch (std::exception* e) {
        std::cout << e->what() << std::endl;
    }
}

int main() {
    Run();
    return 0;
}
