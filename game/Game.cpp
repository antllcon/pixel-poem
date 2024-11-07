// game.cpp

#include "Game.h"
#include "../config.h"
#include <iostream>
#include "../player/Player.h"
#include "../enemy/Enemy.h"

// Конструктор
Game::Game() : state(GameState::Start), deltaTime(0.1f), player(nullptr), enemy(nullptr)
{
    view = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
}

Game::~Game() = default; // unique_ptr автоматически очищает память

// Методы
void Game::processEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (state == GameState::Play && player)
        {
            player->processInput(event, deltaTime, window);
        }
    }
}

void Game::update(sf::RenderWindow& window)
{
    updateDeltaTime();

    switch (state)
    {
    case GameState::Start:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            setState(GameState::Play);
            initEntitiesPlay();
        }
        break;

    case GameState::Play:
        if (player) player->update(deltaTime);
        updateCamera(window);
        break;

    case GameState::Pause:
        break;

    case GameState::End:
        break;
    }
}

void Game::render(sf::RenderWindow& window)
{
    window.clear();

    switch (state)
    {
    case GameState::Start:
        // Рендер меню (в будущем можно добавить)
        break;

    case GameState::Play:
        if (player) player->draw(window);
        if (enemy) enemy->draw(window);
        break;

    case GameState::Pause:
        // Рендер меню паузы
        break;

    case GameState::End:
        // Рендер результатов
        break;
    }

    window.display();
}

void Game::setState(GameState newState) { state = newState; }

Game::GameState Game::getState() const { return state; }

void Game::initEntitiesPlay()
{
    player = std::make_unique<Player>(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED, PLAYER_HEALTH, PLAYER_AIM);
    enemy = std::make_unique<Enemy>(BOT_SIZE, BOT_COLOR, BOT_HEALTH);
    view.setCenter(player->getX(), player->getY());
}

void Game::updateDeltaTime()
{
    deltaTime = clock.restart().asSeconds();
}

void Game::updateCamera(sf::RenderWindow& window)
{
    if (state == GameState::Play && player)
    {
        view.setCenter(player->getX(), player->getY());
    }
    else
    {
        view.setCenter(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    }
    window.setView(view);
}
