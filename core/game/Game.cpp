#include "Game.h"

#include <iostream>

#include "../../Utils.h"
#include "../../entities/enemy/Enemy.h"
#include "../../entities/player/Player.h"
#include "../../systems/map/mapManager.h"
#include "../config.h"

Game::Game()
    // Исправить конструктор, что за srand, поменять объявление map, перенести, убрать view
    : gameStateManager(gameStateManager),
      cameraManager(SCREEN_WIDTH, SCREEN_HEIGHT, CAMERA_DELTA_WIDTH, CAMERA_DELTA_HEIGHT),
      mapManager(MAP_WIDTH, MAP_HEIGHT, ROOM_COUNT),
      end(nullptr),
      ui(nullptr),
      globalTime(0.f),
      deltaTime(0.f),
      lastStateChangeTime(0.f) {
    srand(static_cast<unsigned>(time(nullptr)));
    view = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
}

Game::~Game() = default;

void Game::processEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    switch (gameStateManager.getState()) {
        case GameStateManager::GameState::Start:
            handleStartEvents(window);
            break;

        case GameStateManager::GameState::Play:
            handlePlayEvents();
            break;

        case GameStateManager::GameState::Pause:
            handlePauseEvents();
            break;

        case GameStateManager::GameState::End:
            handleEndEvents();
            break;
    }
}

void Game::handleStartEvents(sf::RenderWindow& window) {
    inputHandler.processInput();
    menu.processMenu(inputHandler);
    if (inputHandler.isPressed("approve")) {
        if (menu.getSelectedOption() == false) {
            changeState(GameStateManager::GameState::Play);
            if (entityManager.getPlayer() == nullptr) {
                initEntitiesPlay();
            }
            gameStateManager.setPlayState(GameStateManager::GamePlayState::Sleep);
        } else if (menu.getSelectedOption() == true) {
            window.close();
        }
    }
    inputHandler.resetStates();
}

void Game::handlePlayEvents() {
    // Стрельба и направление - разобраться!!!
    if (inputHandler.isPressed("exit")) {
        gameStateManager.setState(GameStateManager::GameState::Pause);
    }
    inputHandler.processInput();
    if (entityManager.getPlayer()) {
        entityManager.getPlayer()->processInput(inputHandler, globalTime, entityManager.getBullets());
    }
    sf::Vector2f position(entityManager.getPlayer()->getX(), entityManager.getPlayer()->getY());
    for (auto& enemy : entityManager.getEnemies()) {
        enemy->processInput(position, globalTime, entityManager.getBullets());
    }
    inputHandler.resetStates();
}

void Game::handlePauseEvents() {
    inputHandler.processInput();
    pause.processPause(inputHandler);
    if (inputHandler.isPressed("approve")) {
        if (pause.getSelectedOption() == false) {
            changeState(GameStateManager::GameState::Play);
        } else if (pause.getSelectedOption() == true) {
            changeState(GameStateManager::GameState::Start);
        }
    }
    inputHandler.resetStates();
}

void Game::handleEndEvents() {
    inputHandler.processInput();
    end->processEnd(inputHandler);
    if (inputHandler.isPressed("approve")) {
        if (end->getSelectedOption() == false) {

        } else if (end->getSelectedOption() == true) {
            changeState(GameStateManager::GameState::Start);
        }
    }
    inputHandler.resetStates();
}

void Game::update(sf::RenderWindow& window) {
    updateDeltaTime();
    updateCamera(window);

    switch (gameStateManager.getState()) {
        case GameStateManager::GameState::Start:
            break;

        case GameStateManager::GameState::Play:
            if (!entityManager.getPlayer()->getIsAlive() || entityManager.getPlayer()->getMoney() == 16) {
                changeState(GameStateManager::GameState::End);
            }
            if (inputHandler.isPressed("exit")) {
                changeState(GameStateManager::GameState::Pause);
            }
            if (canChangeState()) {
                collisionManager.checkCollisions(entityManager, mapManager);
            }
            if (entityManager.getPlayer()) entityManager.getPlayer()->update(deltaTime);
            if (ui) {
                ui->update(entityManager.getPlayer()->getHealth(), entityManager.getPlayer()->getArmor(),
                           entityManager.getPlayer()->getMoney());
            }
            entityManager.update(deltaTime);
            if (gameStateManager.getPlayState() == GameStateManager::GamePlayState::Sleep) {
                if (entityManager.getPlayer()) entityManager.getPlayer()->regenerateArmor(globalTime);
            }
            break;

        case GameStateManager::GameState::Pause:

            break;

        case GameStateManager::GameState::End:

            break;
    }
}

void Game::updateDeltaTime() {
    deltaTime = clock.restart().asSeconds();
    globalTime += deltaTime;
}

void Game::updateCamera(sf::RenderWindow& window) {
    if ((gameStateManager.getState() == GameStateManager::GameState::Play && entityManager.getPlayer()) ||
        gameStateManager.getState() == GameStateManager::GameState::Pause || gameStateManager.getState() == GameStateManager::GameState::End) {
        cameraManager.update(view, entityManager.getPlayer());
    } else {
        cameraManager.reset(view);
    }
    window.setView(view);
}

void Game::render(sf::RenderWindow& window) {
    switch (gameStateManager.getState()) {
        case GameStateManager::GameState::Start:
            window.clear(COLOR_DARK);
            menu.renderMenu(inputHandler, window);
            break;

        case GameStateManager::GameState::Play:
            window.clear(COLOR_DARK);
            mapManager.render(window);
            if (entityManager.getPlayer()) entityManager.getPlayer()->draw(window);
            for (const auto& enemy : entityManager.getEnemies()) {
                enemy->draw(window);
            }
            for (const auto& bullet : entityManager.getBullets()) {
                bullet.draw(window);
            }
            window.setView(view);                     // Установка игровой камеры
            window.setView(window.getDefaultView());  // Сброс для интерфейса
            if (ui) ui->render(window);               // Отрисовка UI
            window.setView(view);                     // Возвращение камеры

            break;

        case GameStateManager::GameState::Pause:
            window.clear(COLOR_DARK);
            mapManager.render(window);
            if (entityManager.getPlayer()) entityManager.getPlayer()->draw(window);
            for (const auto& enemy : entityManager.getEnemies()) {
                enemy->draw(window);
            }
            for (const auto& bullet : entityManager.getBullets()) {
                bullet.draw(window);
            }
            window.setView(view);                     // Установка игровой камеры
            window.setView(window.getDefaultView());  // Сброс для интерфейса
            // if (ui) ui->render(window);               // Отрисовка UI
            pause.renderPause(inputHandler, window);
            window.setView(view);                     // Возвращение камеры
            break;

        case GameStateManager::GameState::End:
            window.clear(COLOR_DARK);
            mapManager.render(window);
            if (entityManager.getPlayer()) entityManager.getPlayer()->draw(window);
            for (const auto& enemy : entityManager.getEnemies()) {
                enemy->draw(window);
            }
            for (const auto& bullet : entityManager.getBullets()) {
                bullet.draw(window);
            }
            window.setView(view);                     // Установка игровой камеры
            window.setView(window.getDefaultView());  // Сброс для интерфейса
            // if (ui) ui->render(window);               // Отрисовка UI
            if (end) end->renderEnd(window);
            window.setView(view);                     // Возвращение камеры
            break;
    }

    window.display();
}

void Game::initEntitiesPlay() {
    mapManager.generateMap();
    const auto roomPositions = mapManager.getRoomPositions();

    sf::Vector2f playerRoom = mapManager.getFirstRoomPosition();
    entityManager.spawnEnemies(roomPositions, playerRoom);

    entityManager.spawnPlayer();
    ui = new UI(entityManager.getPlayer()->getHealth(), entityManager.getPlayer()->getArmor(),
                entityManager.getPlayer()->getMoney());
    end = new End(entityManager.getPlayer()->getMoney());
}

GameStateManager& Game::getStateManager() { return gameStateManager; }

bool Game::canChangeState() { return (globalTime - lastStateChangeTime) >= STATE_CHANGE_COOLDOWN; }

void Game::changeState(GameStateManager::GameState newState) {
    if (canChangeState()) {
        gameStateManager.setState(newState);
        lastStateChangeTime = globalTime;
    }
}
