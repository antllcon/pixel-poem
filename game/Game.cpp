// game.cpp

#include "Game.h"
#include "../config.h"
#include <iostream>
#include "../player/Player.h"
#include "../enemy/Enemy.h"

// Конструктор
Game::Game() : selectedOption(0), state(GameState::Start), deltaTime(0.1f), globalTime(0.f), player(nullptr), enemy(nullptr) {
    view = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    initMenu();
    initControllerStatus();
}

// unique_ptr автоматически очищает память
Game::~Game() = default;

// Методы
void Game::processEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (state) {
        case GameState::Start:
            processControllerConnect();
            if (event.type == sf::Event::KeyPressed) {
                processSelectionButton(event);
                processMenu(event, window);
            }
            break;

        case GameState::Play:
            if (player) player->processInput(globalTime);
            break;

        case GameState::Pause:
            break;

        case GameState::End:
            break;
        }
    }
}

void Game::processMenu(const sf::Event& event, sf::RenderWindow& window)  {
    if (event.key.code == sf::Keyboard::Enter) {
        if (selectedOption == 0) {
            setState(GameState::Play);
            initEntitiesPlay();
        } else if (selectedOption == 1) {
            window.close();
        }
    }
}

void Game::processSelectionButton(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
        selectedOption = (!selectedOption) ? 1 : 0;

        startText.setFillColor(selectedOption == 0 ? COLOR_GREEN : COLOR_GRAY);
        exitText.setFillColor(selectedOption == 1 ? COLOR_GREEN : COLOR_GRAY);
    }
}

bool Game::processControllerConnect() {
    sf::Joystick::update();
    if (sf::Joystick::isConnected(0)) return true;
    return false;
}

void Game::update(sf::RenderWindow& window) {
    updateDeltaTime();
    updateCamera(window);

    switch (state) {
    case GameState::Start:
        break;

    case GameState::Play:
        if (player) player->update(deltaTime);
        break;

    case GameState::Pause:
        break;

    case GameState::End:
        break;
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    switch (state) {
    case GameState::Start:
        window.draw(titleText);
        window.draw(subtitleText);
        window.draw(startText);
        window.draw(exitText);
        if (processControllerConnect()) {
            window.draw(spriteController);
        }
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

void Game::initControllerStatus() {
    if (!textureController.loadFromFile(SRC_CONTROLLER)) {
        std::cerr << "Ошибка загрузки картинки!" << std::endl;
    }

    spriteController.setTexture(textureController);
    spriteController.setPosition(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 100);
    spriteController.setScale(0.05f, 0.05f);
}

void Game::initMenu()
{
    if (!font.loadFromFile(SRC_FONT)) {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("Pixel Poem");
    titleText.setCharacterSize(64);
    titleText.setFillColor(COLOR_PURPLE);
    titleText.setPosition(SCREEN_WIDTH / 2.0f - 160, SCREEN_HEIGHT / 2.0f - 150);

    subtitleText.setFont(font);
    subtitleText.setString("Dungeon");
    subtitleText.setCharacterSize(48);
    subtitleText.setFillColor(COLOR_PURPLE);
    subtitleText.setPosition(SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f - 100);

    startText.setFont(font);
    startText.setString("Play");
    startText.setCharacterSize(30);
    startText.setFillColor(COLOR_GREEN);
    startText.setPosition(SCREEN_WIDTH / 2.0f - 30, SCREEN_HEIGHT / 2.0f);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(COLOR_GRAY);
    exitText.setPosition(SCREEN_WIDTH / 2.0f - 30, SCREEN_HEIGHT / 2.0f + 30);
}

void Game::initEntitiesPlay() {
    player = std::make_unique<Player>(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED, PLAYER_HEALTH, PLAYER_AIM);
    enemy = std::make_unique<Enemy>(BOT_SIZE, BOT_COLOR, BOT_HEALTH);
    view.setCenter(player->getX(), player->getY());
}

void Game::updateDeltaTime() {
    deltaTime = clock.restart().asSeconds();
    if (state == GameState::Play) {
        globalTime += deltaTime;
    }
}

void Game::updateCamera(sf::RenderWindow& window) {
    if (state == GameState::Play && player) {
        view.setCenter(player->getX(), player->getY());
    }
    else {
        view.setCenter(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    }
    window.setView(view);
}

void Game::setState(GameState newState) { state = newState; }

Game::GameState Game::getState() const { return state; }
