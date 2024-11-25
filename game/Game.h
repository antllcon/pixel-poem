// Game.h

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../input/Input.h"

class Player;
class Enemy;

class Game
{
public:
    enum class GameState { Start, Play, Pause, End };

    Game();
    // TODO: Убивать игрока тут, убрать unique_ptr
    ~Game();

    void processEvents(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    void setState(GameState newState);
    GameState getState() const;

private:
    // Объявление игрового состояния
    GameState state;

    // Объявление времени
    sf::Clock clock;

    // Переменная среднего времени
    float deltaTime;

    // Отслеживание глобального времени
    float globalTime;

    // Объявление объекта наблюдения
    sf::View view;

    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    void checkCollisions();

    // События ввода
    Input inputHandler;

    // Спрайт ввода
    sf::Texture textureController;
    sf::Sprite spriteController;

    // Тексты
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text winEndText;
    sf::Text lossEndText;
    sf::Text startText;
    sf::Text exitText;

    // Выбранная опция
    int selectedOption;

    // Инициализация меню игры
    void initTextMenu();

    // Инициализация сущностей
    void initEntitiesPlay();

    // Статус подключенного контроллера
    void initControllerStatus();

    // Проверка ввода
    void testInputHandler();

    // Процесс работы с меню
    void processMenu(sf::RenderWindow& window);

    // Процесс выбора кнопки
    void processSelectionButton();

    // Обновление дельты времени
    void updateDeltaTime();

    // Обновление наблюдения камеры
    void updateCamera(sf::RenderWindow& window);

    // Отрисовка меню игры
    void renderMenu(sf::RenderWindow& window);
};
