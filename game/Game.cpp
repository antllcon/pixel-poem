#include "Game.h"

#include "../config.h"
#include "../enemy/Enemy.h"
#include "../player/Player.h"

Game::Game() : state(GameState::Start), globalTime(0.f), deltaTime(0.1f) {
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
            // Проверка коллизий
            if (player) player->update(deltaTime);
            updateEnemy();
            updateBullets();
            break;

        case GameState::Pause:
            break;

        case GameState::End:
            break;
    }
}

void Game::updateEnemy() {
    for (auto& enemy : enemies) {
        enemy->update(deltaTime);
    }
}

void Game::updateBullets() {
    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }
    std::erase_if(bullets, [](const Bullet& b) { return !b.isActive(); });
}

void Game::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    switch (state) {
        case GameState::Start:
            menu.renderMenu(inputHandler, window);
            break;

        case GameState::Play:
            if (player) player->draw(window);
            for (const auto& enemy : enemies) {
                enemy->draw(window);
            }
            for (const auto& bullet : bullets) {
                bullet.draw(window);
            }
            break;

        case GameState::Pause:
            break;

        case GameState::End:
            break;
    }

    window.display();
}

void Game::initEntitiesPlay() {
    spawnPlayer();
    spawnEnemies(NUM_ENEMIES);
}

void Game::spawnPlayer() {
    player = std::make_unique<Player>(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED,
                                      PLAYER_HEALTH);
}

void Game::spawnEnemies(int numEnemies) {
    for (int i = 0; i < numEnemies; ++i) {
        float x = static_cast<float>(rand() % SCREEN_WIDTH);
        float y = static_cast<float>(rand() % SCREEN_HEIGHT);
        auto enemy = std::make_unique<Enemy>(BOT_COLOR, BOT_HEALTH, BOT_SPEED,
                                             BOT_DIRECTION_CHANGE_INTERVAL,
                                             BOT_DIRECTION_CHANGE_TIME);
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
        float cameraLeft =
            view.getCenter().x - SCREEN_WIDTH / 2.0f + CAMERA_DELTA_WIDTH;
        float cameraRight =
            view.getCenter().x + SCREEN_WIDTH / 2.0f - CAMERA_DELTA_WIDTH;
        float cameraTop =
            view.getCenter().y - SCREEN_HEIGHT / 2.0f + CAMERA_DELTA_HEIGHT;
        float cameraBottom =
            view.getCenter().y + SCREEN_HEIGHT / 2.0f - CAMERA_DELTA_HEIGHT;

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

// void Game::checkCollisions() {
//     // Проверка пуль игрока с врагами
//     for (auto& bullet : player->getBullets()) {
//         for (auto& enemy : enemies) {
//             if (bullet.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
//                 enemy->takeDamage(bullet.getDamage());
//                 bullet.setInactive();  // Или удаляем пулю
//             }
//         }
//     }
//
//     // Проверка врагов с игроком
//     for (auto& enemy : enemies) {
//         if (enemy->getGlobalBounds().intersects(player->getGlobalBounds())) {
//             player->takeDamage(enemy->getDamage());
//         }
//     }
//
//     // Проверка пуль врагов с игроком (если у врагов есть пули)
//     for (const auto& enemy : enemies) {
//         for (const auto& bullet : enemy->getBullets()) {
//             if (bullet.getGlobalBounds().intersects(
//                     player->getGlobalBounds())) {
//                 player->takeDamage(bullet.getDamage());
//                 bullet.setInactive();  // Или удаляем пулю
//             }
//         }
//     }
// }

void Game::setState(GameState newState) { state = newState; }

Game::GameState Game::getState() const { return state; }
