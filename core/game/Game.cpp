#include "Game.h"

#include <iostream>

#include "../../Utils.h"
#include "../../entities/enemy/Enemy.h"
#include "../../entities/player/Player.h"
#include "../../systems/map/Map.h"
#include "../config.h"

Game::Game()
    // Исправить конструктор, что за srand, поменять объявление map, перенести, убрать view
    : gameStateManager(gameStateManager), map(MAP_WIDTH, MAP_HEIGHT), ui(nullptr), globalTime(0.f), deltaTime(0.1f) {
    srand(static_cast<unsigned>(time(nullptr)));
    view = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

    // Перенести карту в сущности
    map.placeRooms(map, ROOM_COUNT);
    map.connectRooms(map);
    map.printMap();

    entityManager.spawnPlayer();
    entityManager.spawnEnemies();
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
            initEntitiesPlay();
            gameStateManager.setState(GameStateManager::GameState::Play);
        } else if (menu.getSelectedOption() == true) {
            window.close();
        }
    }
    inputHandler.resetStates();
}

// Стрельба и направление - разобраться!!!
void Game::handlePlayEvents() {
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
    inputHandler.resetStates();
}

void Game::handleEndEvents() {
    inputHandler.processInput();
    inputHandler.resetStates();
}

void Game::update(sf::RenderWindow& window) {
    updateDeltaTime();
    updateCamera(window);

    switch (gameStateManager.getState()) {
        case GameStateManager::GameState::Start:
            break;

        case GameStateManager::GameState::Play:
            // обработка коллизий и изменение состояний игрока - разобраться!!!
            // вынести это в методы
            checkCollisions();

            if (entityManager.getPlayer()) entityManager.getPlayer()->update(deltaTime);
            if (ui) {
                ui->update(entityManager.getPlayer()->getHealth(), entityManager.getPlayer()->getArmor(),
                           entityManager.getPlayer()->getMoney());
            }
            entityManager.update(deltaTime);
            if (gameStateManager.getPlayState() == GameStateManager::GamePlayState::Sleep) {
                if (entityManager.getPlayer()) entityManager.getPlayer()->regenerateArmor(globalTime);
            }
            if (!entityManager.getPlayer()->getIsAlive()) {
                gameStateManager.setState(GameStateManager::GameState::Pause);
            }
            break;

        case GameStateManager::GameState::Pause:
            break;

        case GameStateManager::GameState::End:
            break;
    }
}

void Game::render(sf::RenderWindow& window) {
    switch (gameStateManager.getState()) {
        case GameStateManager::GameState::Start:
            window.clear(COLOR_DARK);
            menu.renderMenu(inputHandler, window);
            break;

        case GameStateManager::GameState::Play:
            window.clear(COLOR_DARK_PURPLE);
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
            break;

        case GameStateManager::GameState::End:
            window.clear(COLOR_DARK_PURPLE);
            break;
    }

    window.display();
}

void Game::initEntitiesPlay() {
    entityManager.spawnPlayer();
    // Нужна ли обертка, стоит ли так вызывать конструктор?
    ui = new UI(entityManager.getPlayer()->getHealth(), entityManager.getPlayer()->getArmor(), entityManager.getPlayer()->getMoney());
    entityManager.spawnEnemies();
}

void Game::updateDeltaTime() {
    deltaTime = clock.restart().asSeconds();
    if (gameStateManager.getState() == GameStateManager::GameState::Play) {
        globalTime += deltaTime;
    }
}

void Game::updateCamera(sf::RenderWindow& window) {
    if (gameStateManager.getState() == GameStateManager::GameState::Play && entityManager.getPlayer()) {
        float cameraLeft = view.getCenter().x - CAMERA_DELTA_WIDTH;
        float cameraRight = view.getCenter().x + CAMERA_DELTA_WIDTH;
        float cameraTop = view.getCenter().y - CAMERA_DELTA_HEIGHT;
        float cameraBottom = view.getCenter().y + CAMERA_DELTA_HEIGHT;

        if (entityManager.getPlayer()->getX() < cameraLeft) {
            view.move(entityManager.getPlayer()->getX() - cameraLeft, 0);
        }
        if (entityManager.getPlayer()->getX() > cameraRight) {
            view.move(entityManager.getPlayer()->getX() - cameraRight, 0);
        }
        if (entityManager.getPlayer()->getY() < cameraTop) {
            view.move(0, entityManager.getPlayer()->getY() - cameraTop);
        }
        if (entityManager.getPlayer()->getY() > cameraBottom) {
            view.move(0, entityManager.getPlayer()->getY() - cameraBottom);
        }
    } else {
        view.setCenter(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    }
    window.setView(view);
}

void Game::checkCollisions() {
    checkBulletEnemyCollisions();   // Пули игрока ↔ Враги
    checkBulletPlayerCollisions();  // Пули врагов ↔ Игрок
    checkPlayerEnemyCollisions();   // Игрок ↔ Враги
}

void Game::checkPlayerEnemyCollisions() {
    for (auto& enemy : entityManager.getEnemies()) {
        sf::FloatRect viewAreaBounds = enemy->getGlobalBounds();
        sf::FloatRect viewArea = addFloatRects(viewAreaBounds, BOT_VIEW_AREA);
        if (entityManager.getPlayer()->getGlobalBounds().intersects(viewArea)) {
            enemy->setState(EnemyState::attack);
        } else {
            if (enemy->getState() == EnemyState::attack) {
                enemy->setState(EnemyState::sleep);
            }
        }
    }
}

void Game::checkBulletEnemyCollisions() {
    for (auto& bullet : entityManager.getBullets()) {
        if (bullet.getOwnerType() == Bullet::OwnerType::Player) {
            for (auto& enemy : entityManager.getEnemies()) {
                if (bullet.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
                    enemy->takeDamage(bullet.getDamage());
                    bullet.setActive(false);
                }
            }
        }
    }
}

void Game::checkBulletPlayerCollisions() {
    for (auto& bullet : entityManager.getBullets()) {
        if (bullet.getOwnerType() == Bullet::OwnerType::Bot) {
            if (bullet.getGlobalBounds().intersects(entityManager.getPlayer()->getGlobalBounds())) {
                entityManager.getPlayer()->takeDamage(bullet.getDamage());
                bullet.setActive(false);
            }
        }
    }
}

GameStateManager& Game::getStateManager() { return gameStateManager; }
