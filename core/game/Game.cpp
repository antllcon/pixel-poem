#include "Game.h"

#include <iostream>

#include "../../Utils.h"
#include "../../entities/enemy/Enemy.h"
#include "../../entities/player/Player.h"
#include "../../systems/map/MapManager.h"
#include "../config.h"

Game::Game()
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

void Game::processEvents(sf::RenderWindow &window) {
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

void Game::handleStartEvents(sf::RenderWindow &window) {
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
    if (inputHandler.isPressed("exit")) {
        gameStateManager.setState(GameStateManager::GameState::Pause);
    }

    inputHandler.processInput();
    if (entityManager.getPlayer()) {
        entityManager.getPlayer()->processInput(inputHandler, globalTime, entityManager.getBullets());
    }
    sf::Vector2f position(entityManager.getPlayer()->getX(), entityManager.getPlayer()->getY());
    // Наблюдаем за игроком
    for (auto &enemy: entityManager.getEnemies()) {
        enemy->processInput(position, globalTime, entityManager.getBullets());
    }
    for (auto &money: entityManager.getMoneys()) {
        money->processInput(position);
    }
    if (entityManager.getBoss()) {
        entityManager.getBoss()->processInput(position, globalTime, entityManager.getBullets());
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

void Game::update(sf::RenderWindow &window) {
    updateDeltaTime();
    updateCamera(window);

    switch (gameStateManager.getState()) {
        case GameStateManager::GameState::Start:
            break;

        case GameStateManager::GameState::Play:
            if (!entityManager.getPlayer()->getIsAlive() || !entityManager.getBoss()->getIsAlive()) {
                changeState(GameStateManager::GameState::End);
                end = new End(entityManager.getPlayer()->getMoney());
            }
            if (canChangeState()) {
                collisionManager.checkCollisions(entityManager, mapManager);
            }
            if (inputHandler.isPressed("exit")) {
                changeState(GameStateManager::GameState::Pause);
            }
            if (ui) {
                ui->update(entityManager.getPlayer()->getHealth(), entityManager.getPlayer()->getArmor(),
                           entityManager.getPlayer()->getMoney(), entityManager.getPlayer()->getWeapon(),
                           mapManager.getMap(), entityManager.getPlayer()->getPosition(),
                           mapManager.getPlayerRoomPosition(), mapManager.getBossRoomPosition(),
                           mapManager.getShopRoomPosition());
            }
            entityManager.update(deltaTime);

            if (gameStateManager.getPlayState() == GameStateManager::GamePlayState::Sleep) {
                if (entityManager.getPlayer()) entityManager.getPlayer()->regenerateArmor(globalTime);
            }
            if (gameStateManager.getPlayState() == GameStateManager::GamePlayState::Attack) {

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

void Game::updateCamera(sf::RenderWindow &window) {
    if ((gameStateManager.getState() == GameStateManager::GameState::Play && entityManager.getPlayer()) ||
        gameStateManager.getState() == GameStateManager::GameState::Pause ||
        gameStateManager.getState() == GameStateManager::GameState::End) {
        cameraManager.update(view, entityManager.getPlayer());
    } else {
        cameraManager.reset(view);
    }
    window.setView(view);
}

void Game::render(sf::RenderWindow &window) {
    switch (gameStateManager.getState()) {
        case GameStateManager::GameState::Start:
            window.clear(COLOR_BRAUN);
            menu.renderMenu(inputHandler, window);
            break;

        case GameStateManager::GameState::Play:
            window.clear(COLOR_BRAUN);
            mapManager.render(window);
            entityManager.render(window);
            window.setView(view);
            window.setView(window.getDefaultView());
            if (ui) ui->render(window);
            window.setView(view);
            break;

        case GameStateManager::GameState::Pause:
            window.clear(COLOR_BRAUN);
            mapManager.render(window);
            entityManager.render(window);
            window.setView(view);
            window.setView(window.getDefaultView());
            pause.renderPause(inputHandler, window);
            window.setView(view);
            break;

        case GameStateManager::GameState::End:
            window.clear(COLOR_BRAUN);
            mapManager.render(window);
            entityManager.render(window);
            window.setView(view);
            window.setView(window.getDefaultView());
            if (end) end->renderEnd(window);
            window.setView(view);
            break;
    }

    window.display();
}

void Game::initEntitiesPlay() {
    mapManager.generateMap();
    const auto roomPositions = mapManager.getRoomPositions();
    sf::Vector2f playerRoom = mapManager.getPlayerRoomPosition();
    sf::Vector2f bossRoom = mapManager.getBossRoomPosition();
    sf::Vector2f shopRoom = mapManager.getShopRoomPosition();
    std::cout << " Появление врагов " << std::endl;
    entityManager.spawnEnemies(roomPositions, playerRoom);
    std::cout << " Появление монет " << std::endl;
    entityManager.spawnMoney(roomPositions, playerRoom);
    std::cout << " Появление игрока " << std::endl;
    entityManager.spawnPlayer(playerRoom);
    std::cout << " Появление босса " << std::endl;
    entityManager.spawnBoss(bossRoom);
    std::cout << " Появление вещей в магазине " << std::endl;
    entityManager.spawnShopItems(shopRoom);

    ui = new UI(entityManager.getPlayer()->getHealth(), entityManager.getPlayer()->getArmor(),
                entityManager.getPlayer()->getMoney(), entityManager.getPlayer()->getWeapon());
}

GameStateManager &Game::getStateManager() { return gameStateManager; }

bool Game::canChangeState() { return (globalTime - lastStateChangeTime) >= STATE_CHANGE_COOLDOWN; }

void Game::changeState(GameStateManager::GameState newState) {
    if (canChangeState()) {
        gameStateManager.setState(newState);
        lastStateChangeTime = globalTime;
    }
}
