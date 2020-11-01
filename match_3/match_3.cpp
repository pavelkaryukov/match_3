#include "game_controller/game_controller.h"
#include <iostream>

int main() {
    std::shared_ptr<GameRender> render = std::make_shared<GameRender>();	// Создаем представление
    GameController controller(render);	// Создаем контроллер
    try {
        controller.Run(); // Запускаем игру
    }
    catch (std::exception* e) {
        std::cout << e->what() << std::endl;
    }

    return 0;
}
