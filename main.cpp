// main.cpp

#include <SFML/Graphics.hpp>
#include "config.h"
#include "player/Player.h"
#include "game/Game.h"
#include "enemy/Enemy.h"

int main()
{
    // Инициализация игры
    Game pixelPoem;
    pixelPoem.setState(Game::GameState::Play);
    // Инициализация игрока
    Player player(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED, PLAYER_HEALTH, PLAYER_AIM);
    // Инициализация бота
    Enemy enemy(BOT_SIZE, BOT_COLOR, BOT_HEALTH);
    // Инициализация экрана
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Pixel Poem");
    // Инициализация вида
    sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    view.setCenter(player.getX(), player.getY());

    // Цикл игры
    while (window.isOpen())
    {
        pixelPoem.processEvents(window, player, enemy);
        pixelPoem.updateDeltaTime();
        pixelPoem.updateCamera(window, view, player);
        pixelPoem.update(player, enemy);
        pixelPoem.render(window, player, enemy);
    }
    return 0;
}
