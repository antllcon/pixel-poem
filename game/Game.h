#pragma once

#include <SFML/Graphics.hpp>
#include "../player/Player.h"

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
	void setState(GameState newState);
	GameState getState() const;
	void update(float deltaTime, Player &player);

private:
	GameState state;
	Player player(int size, sf::Color color, float speed, int health);
};
