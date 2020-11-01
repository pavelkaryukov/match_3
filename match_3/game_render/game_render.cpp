#include "game_render.h"
#include "../assets/assets.h"

GameRender::GameRender() {
    Init();
}

struct GameModel {
    static const int SIZE = 4;			        // Размер игрового поля в плашках
    static const int ARRAY_SIZE = SIZE * SIZE;	// Размер массива
    static const int FIELD_SIZE = 500;		    // Размер игрового поля в пикселях
    static const int CELL_SIZE = 120;		    // Размер плашки в пикселях
    static const int RENDER_X = 740;
    static const int RENDER_Y = 480;
};

bool GameRender::Init() {
    setPosition(50.f, 50.f);
    // Создаем окно размером 600 на 600 и частотой обновления 60 кадров в секунду
    m_Window.create(sf::VideoMode(600, 600), "15");
    m_Window.setFramerateLimit(60);
    // Текст с обозначением клавиш
    m_Text = sf::Text("F2 - New Game / Esc - Exit / Arrow Keys - Move Tile", Assets::Instance().GetFont(), 20);
    m_Text.setFillColor(sf::Color::Cyan);
    m_Text.setPosition(5.f, 5.f);
    return true;
}

void GameRender::Render() {
    m_Window.clear();
    m_Window.draw(*this);
    m_Window.draw(m_Text);
    m_Window.display();
}

void GameRender::ChangeText(std::string&& aStr) {
    m_Text.setString(std::move(aStr));
}

void GameRender::draw(sf::RenderTarget& aTarget, sf::RenderStates aStates) const {
    aStates.transform *= getTransform();
    sf::Color color = sf::Color(200, 100, 200);

    // Рисуем рамку игрового поля
    sf::RectangleShape shape(sf::Vector2f(GameModel::FIELD_SIZE, GameModel::FIELD_SIZE));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(0, 0);//Сместили позицию для второго текста
    aTarget.draw(shape, aStates);

    // Подготавливаем рамку для отрисовки всех плашек
    shape.setSize(sf::Vector2f(GameModel::CELL_SIZE - 2, GameModel::CELL_SIZE - 2));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(sf::Color::Transparent);

    // Подготавливаем текстовую заготовку для отрисовки номеров плашек
    sf::Text text("", Assets::Instance().GetFont(), 52);
    //DrawElements(shape, text, color, aTarget, aStates);
}
