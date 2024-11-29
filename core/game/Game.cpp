#include "Game.h"

#include <iostream>

#include "../../Utils.h"
#include "../../entities/enemy/Enemy.h"
#include "../../entities/player/Player.h"
#include "../../systems/map/Map.h"
#include "../config.h"

Game::Game()
    : state(GameState::Start),
      playState(GamePlayState::Sleep),
      map(MAP_WIDTH, MAP_HEIGHT),
      ui(nullptr),
      globalTime(0.f),
      deltaTime(0.1f) {
    srand(static_cast<unsigned>(time(nullptr)));
    view = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

    map.placeRooms(map, ROOM_COUNT);
    map.connectRooms(map);

    map.printMap();
}

Game::~Game() = default;

void Game::processEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    switch (state) {
        case GameState::Start:
            handleStartEvents(window);
            break;

        case GameState::Play:
            handlePlayEvents();
            break;

        case GameState::Pause:
            handlePauseEvents();
            break;

        case GameState::End:
            handleEndEvents();
            break;
    }
}

void Game::handleStartEvents(sf::RenderWindow& window) {
    inputHandler.processInput();
    menu.processMenu(inputHandler);
    if (inputHandler.isPressed("approve")) {
        if (menu.getSelectedOption() == 0) {
            initEntitiesPlay();
            setState(GameState::Play);
        } else if (menu.getSelectedOption() == 1) {
            window.close();
        }
    }
    inputHandler.resetStates();
}

void Game::handlePlayEvents() {
    inputHandler.processInput();
    if (player) player->processInput(inputHandler, globalTime, bullets);
    sf::Vector2f position(player->getX(), player->getY());
    for (auto& enemy : enemies) {
        enemy->processInput(position, globalTime, bullets);
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

    switch (state) {
        case GameState::Start:
            break;

        case GameState::Play:
            checkCollisions();
            if (player) player->update(deltaTime);
            if (ui)
                ui->update(player->getHealth(), player->getArmor(),
                           player->getMoney());
            updateEnemy();
            updateBullets();
            if (playState == GamePlayState::Sleep) {
                if (player) player->regenerateArmor(globalTime);
            }
            if (!player->getIsAlive()) {
                setState(GameState::Pause);
            }
            break;

        case GameState::Pause:
            if (ui)
                ui->update(player->getHealth(), player->getArmor(),
                           player->getMoney());
            updateEnemy();
            updateBullets();
            if (playState == GamePlayState::Sleep) {
                if (player) player->regenerateArmor(globalTime);
            }
            break;

        case GameState::End:
            break;
    }
}

void Game::updateEnemy() {
    for (auto& enemy : enemies) {
        enemy->update(deltaTime);
    }
    std::erase_if(enemies, [](const std::unique_ptr<Enemy>& enemy) {
        return !enemy->getIsAlive();
    });
}

void Game::updateBullets() {
    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }
    std::erase_if(bullets,
                  [](const Bullet& bullet) { return !bullet.isActive(); });
}

void Game::render(sf::RenderWindow& window) {
    switch (state) {
        case GameState::Start:
            window.clear(COLOR_DARK);
            menu.renderMenu(inputHandler, window);
            break;

        case GameState::Play:
            window.clear(COLOR_DARK_PURPLE);
            if (player) player->draw(window);
            for (const auto& enemy : enemies) {
                enemy->draw(window);
            }
            for (const auto& bullet : bullets) {
                bullet.draw(window);
            }
            window.setView(view);
            window.setView(window.getDefaultView());
            if (ui) ui->render(window);
            window.setView(view);

            break;

        case GameState::Pause:
            break;

        case GameState::End:
            window.clear(COLOR_DARK_PURPLE);
            break;
    }

    window.display();
}

void Game::initEntitiesPlay() {
    spawnPlayer();
    ui = new UI(player->getHealth(), player->getArmor(), player->getMoney());
    spawnEnemies(NUM_ENEMIES);
}

void Game::spawnPlayer() {
    player =
        std::make_unique<Player>(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED,
                                 PLAYER_HEALTH, PLAYER_ARMOR, PLAYER_MONEY);
}

void Game::spawnEnemies(int numEnemies) {
    for (int i = 0; i < numEnemies; ++i) {
        float x = static_cast<float>(rand() % SCREEN_WIDTH);
        float y = static_cast<float>(rand() % SCREEN_HEIGHT);
        auto enemy = std::make_unique<Enemy>(
            EnemyState::sleep, BOT_COLOR, BOT_HEALTH, BOT_SPEED,
            BOT_DIRECTION_CHANGE_INTERVAL, BOT_DIRECTION_CHANGE_TIME);
        enemy->setPosition(x, y);
        enemies.push_back(std::move(enemy));
    }
}

void Game::updateDeltaTime() {
    deltaTime = clock.restart().asSeconds();
    if (state == GameState::Play) {
        globalTime += deltaTime;
    }
}

void Game::updateCamera(sf::RenderWindow& window) {
    if (state == GameState::Play && player) {
        float cameraLeft = view.getCenter().x - CAMERA_DELTA_WIDTH;
        float cameraRight = view.getCenter().x + CAMERA_DELTA_WIDTH;
        float cameraTop = view.getCenter().y - CAMERA_DELTA_HEIGHT;
        float cameraBottom = view.getCenter().y + CAMERA_DELTA_HEIGHT;

        if (player->getX() < cameraLeft) {
            view.move(player->getX() - cameraLeft, 0);
        }
        if (player->getX() > cameraRight) {
            view.move(player->getX() - cameraRight, 0);
        }
        if (player->getY() < cameraTop) {
            view.move(0, player->getY() - cameraTop);
        }
        if (player->getY() > cameraBottom) {
            view.move(0, player->getY() - cameraBottom);
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
    for (auto& enemy : enemies) {
        sf::FloatRect viewAreaBounds = enemy->getGlobalBounds();
        sf::FloatRect viewArea = addFloatRects(viewAreaBounds, BOT_VIEW_AREA);
        if (player->getGlobalBounds().intersects(viewArea)) {
            enemy->setState(EnemyState::attack);
        } else {
            if (enemy->getState() == EnemyState::attack) {
                enemy->setState(EnemyState::sleep);
            }
        }
    }
}

void Game::checkBulletEnemyCollisions() {
    for (auto& bullet : bullets) {
        if (bullet.getOwnerType() == Bullet::OwnerType::Player) {
            for (auto& enemy : enemies) {
                if (bullet.getGlobalBounds().intersects(
                        enemy->getGlobalBounds())) {
                    enemy->takeDamage(bullet.getDamage());
                    bullet.setActive(false);
                }
            }
        }
    }
}

void Game::checkBulletPlayerCollisions() {
    for (auto& bullet : bullets) {
        if (bullet.getOwnerType() == Bullet::OwnerType::Bot) {
            if (bullet.getGlobalBounds().intersects(
                    player->getGlobalBounds())) {
                player->takeDamage(bullet.getDamage());
                bullet.setActive(false);
            }
        }
    }
}

void Game::setState(GameState newState) { state = newState; }

Game::GameState Game::getState() const { return state; }
