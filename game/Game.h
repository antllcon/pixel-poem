#pragma once

#include <SFML/Graphics.hpp>
#include "../player/Player.h"
#include "../enemy/Enemy.h"

class Game
{
public:
    // Перечисление состояний
    enum class GameState
    {
        Start, // Начальное состояние - меню игры
        Play, // Игровое состояние - игровой процесс
        Pause, // Прерывание игрового состояния - пауза
        End // Окончание игрового состояния - конец, итоги игры
    };

    // Конструктор
    Game();

    // Методы
    void processEvents(sf::RenderWindow& window, Player& player, Enemy& enemy);
    void updateDeltaTime();
    void update(Player& player, Enemy& enemy);
    static void updateCamera(sf::RenderWindow& window, sf::View& view, const Player& player);
    static void render(sf::RenderWindow& window, Player& player, Enemy& enemy);

    // Сеттеры и геттеры
    void setState(GameState newState);
    GameState getState() const;

private:
    GameState state;
    sf::Clock clock;
    float deltaTime;
};
