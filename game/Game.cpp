// Game.cpp

#include "Game.h"

// Конструктор
Game::Game() { state = GameState::Start; }

// Сетеры
void Game::setState(GameState newState) { state = newState; }

// Гетеры
Game::GameState Game::getState() const { return state; }

// Методы
void Game::update(float deltaTime, Player &player)
{
	switch (state)
	{
		case GameState::Start:
			// Запуск меню
			// Есть условие перехода в состояние Play
			setState(GameState::Play);
			break;
		case GameState::Play:
			player.processInput();
			player.update(deltaTime);
			// Считывание события паузы игры
			// Условие перехода в Pause
			// Проверка коллизии - функция должна быть в game? или нужен класс collision?
			// Если игрок погиб
			// Условие выхода в состояние конец
			break;
		case GameState::Pause:
			// Запуск меню паузы
			// Условие выхода по считыванию нажатия
			break;
		case GameState::End:
			// Запуск результатов - очки
			// Условие перехода в меню
			break;
	}
}
