// Game.cpp

#include "Game.h"

// Конструктор
Game::Game() { state = GameState::Start; deltaTime = 0.1f; }

// Методы
void Game::processEvents(sf::RenderWindow& window, Player& player, Enemy& enemy)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        player.processInput(event, deltaTime);
        // TODO дописать для бота обработку ввода событий
        // enemy.processInput(event);
    }
}

void Game::updateDeltaTime() {
    deltaTime = clock.restart().asSeconds();
}

void Game::update(Player& player, Enemy& enemy)
{
    switch (state)
    {
    case GameState::Start:
        // Запуск меню
        // Есть условие перехода в состояние Play
        setState(GameState::Play);
        break;
    case GameState::Play:
        player.update(deltaTime);
        // TODO написать обновление для бота
        // enemy.update(deltaTime);
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

void Game::updateCamera(sf::RenderWindow& window, sf::View& view, const Player& player)
{
    view.setCenter(player.getX(), player.getY());
    window.setView(view);
}

void Game::render(sf::RenderWindow& window, Player& player, Enemy& enemy)
{
    window.clear();
    player.draw(window);
    enemy.draw(window);
    window.display();
}

// Сеттеры и геттеры
void Game::setState(GameState newState) { state = newState; }

Game::GameState Game::getState() const { return state; }
