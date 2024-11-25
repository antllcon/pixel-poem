// game.cpp

#include "Game.h"
#include "../config.h"
#include <iostream>
#include "../player/Player.h"
#include "../enemy/Enemy.h"

// Конструктор
Game::Game()
    : state(GameState::Start), deltaTime(0.1f), globalTime(0.f), selectedOption(0) {
    srand(static_cast<unsigned>(time(nullptr)));
    view = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    initTextMenu();
    initControllerStatus();
}

// unique_ptr автоматически очищает память
Game::~Game() = default;

void Game::processEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        inputHandler.processInput();
        switch (state) {
        case GameState::Start:
            // testInputHandler();
            processMenu(window);
            processSelectionButton();
            break;

        case GameState::Play:
            if (player) player->processInput(inputHandler, globalTime);

            // Тестовая отладка
            if (inputHandler.isPressed("exit")) {
                setState(GameState::End);
            }
            break;

        case GameState::Pause:
            break;

        case GameState::End:
            processMenu(window);
            processSelectionButton();
            break;
        }
    }
    inputHandler.resetStates();
}

void Game::update(sf::RenderWindow& window) {

    updateDeltaTime();
    updateCamera(window);

    switch (state) {
    case GameState::Start:
        break;

    case GameState::Play:
        // цикл по массиву
        if (player) player->update(deltaTime);
        for (auto& enemy : enemies) {
            enemy->update(deltaTime);
        }
        // checkCollisions();
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
        renderMenu(window);
        break;

    case GameState::Play:
        if (player) player->draw(window);
        for (const auto& enemy : enemies) {
            enemy->draw(window);
        }
        break;

    case GameState::Pause:
        // Рендер меню паузы

        break;

    case GameState::End:
        // Рендер результатов
        if (player->getHealth() > 0) {
                window.draw(winEndText);
            } else {
                window.draw(lossEndText);
            }
        window.draw(startText);
        window.draw(exitText);
        break;
    }

    window.display();
}





void Game::renderMenu(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(startText);
    window.draw(exitText);
    if (inputHandler.processControllerConnect()) {
        window.draw(spriteController);
    }
}

void Game::testInputHandler() {
    if (inputHandler.isPressed("moveUp")) {
    }
}

void Game::processMenu(sf::RenderWindow& window) {
    if (inputHandler.isPressed("approve")) {
        if (selectedOption == 0) {
            setState(GameState::Play);
            initEntitiesPlay();
        }
        else if (selectedOption == 1) {
            window.close();
        }
    }
    // if (inputHandler.isPressed("exit")) {
    //     window.close();
    // }
}

void Game::processSelectionButton() {
    if (inputHandler.isPressed("moveUp")) {
        selectedOption = 0;
        startText.setFillColor(COLOR_GREEN);
        exitText.setFillColor(COLOR_GRAY);
    }
    if (inputHandler.isPressed("moveDown")) {
        selectedOption = 1;
        exitText.setFillColor(COLOR_GREEN);
        startText.setFillColor(COLOR_GRAY);
    }
}

void Game::initControllerStatus() {
    if (!textureController.loadFromFile(SRC_CONTROLLER)) {
        std::cerr << "Ошибка загрузки картинки!" << std::endl;
    }

    spriteController.setTexture(textureController);
    spriteController.setPosition(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 100);
    spriteController.setScale(0.05f, 0.05f);
}

void Game::initTextMenu() {
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

    winEndText.setFont(font);
    winEndText.setString("You are win!");
    winEndText.setCharacterSize(64);
    winEndText.setFillColor(COLOR_PURPLE);
    winEndText.setPosition(SCREEN_WIDTH / 2.0f - 160, SCREEN_HEIGHT / 2.0f - 150);

    lossEndText.setFont(font);
    lossEndText.setString("You are loss!");
    lossEndText.setCharacterSize(64);
    lossEndText.setFillColor(COLOR_RED);
    lossEndText.setPosition(SCREEN_WIDTH / 2.0f - 160, SCREEN_HEIGHT / 2.0f - 150);

}

void Game::initEntitiesPlay() {
    player = std::make_unique<Player>(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED, PLAYER_HEALTH, PLAYER_AIM);
    // Создание нескольких врагов
    for (int i = 0; i < NUM_ENEMIES; ++i) {
        float x = static_cast<float>(rand() % SCREEN_WIDTH);
        float y = static_cast<float>(rand() % SCREEN_HEIGHT);
        auto enemy = std::make_unique<Enemy>(BOT_COLOR, BOT_HEALTH, BOT_SPEED, BOT_DIRECTION_CHANGE_INTERVAL,
                                             BOT_DIRECTION_CHANGE_TIME);
        enemy->setPosition(x, y);
        enemies.push_back(std::move(enemy));
    }
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
