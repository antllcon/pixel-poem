// main.cpp
#include <SFML/Graphics.hpp>
#include "config.h"
#include "player/Player.h"
#include "game/Game.h"
#include "enemy/Enemy.h"

// Функция проверки закрытия окна
static void eventClose(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

// Функция обновления времени между кадрами
static float updateDeltaTime(sf::Clock &clock)
{
	sf::Time elapsed = clock.restart();
	return elapsed.asSeconds();
}

// Функция отрисовки
static void render(sf::RenderWindow &window, Player &player, Enemy &enemy)
{
	window.clear();
	player.draw(window);
	enemy.draw(window);
	window.display();
}

int main()
{
	// Инициализация игры
	Game pixelPoem;
	pixelPoem.setState(Game::GameState::Play);
	// Инициализация игрока
	Player player(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED, PLAYER_HEALTH);
	// Инициализация бота
	Enemy enemy(BOT_SIZE, BOT_COLOR, BOT_HEALTH);
	// Инициализация экрана
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
	                        "Pixel Poem");
	// Инициализация часов
	sf::Clock clock;
	// Цикл игры
	while (window.isOpen())
	{
		eventClose(window);
		float deltaTime = updateDeltaTime(clock);
		pixelPoem.update(deltaTime, player);
		render(window, player, enemy);
	}
	return 0;
}
