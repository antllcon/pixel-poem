#include "./EntitiyManager.h"
#include "../../core/config.h"

EntityManager::EntityManager() = default;
EntityManager::~EntityManager() = default;

void EntityManager::spawnPlayer() {
    // Исправить player - не передавать size, color
    player = std::make_unique<Player>(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED, PLAYER_HEALTH, PLAYER_ARMOR, PLAYER_MONEY);
}

Player* EntityManager::getPlayer() {
    return player.get();
}

void EntityManager::spawnEnemies() {
    for (int i = 0; i < NUM_ENEMIES; ++i) {
        // Изменить для комнат расположение
        float x = static_cast<float>(rand() % SCREEN_WIDTH);
        float y = static_cast<float>(rand() % SCREEN_HEIGHT);
        // Исправить enemy - не передавать color, interval, подумать, что передавать
        auto enemy = std::make_unique<Enemy>(EnemyState::sleep, BOT_COLOR, BOT_HEALTH, BOT_SPEED,
                                             BOT_DIRECTION_CHANGE_INTERVAL, BOT_DIRECTION_CHANGE_TIME);
        enemy->setPosition(x, y);
        enemies.push_back(std::move(enemy));
    }
}

const std::vector<std::unique_ptr<Enemy>>& EntityManager::getEnemies() const {
    return enemies;
}

void EntityManager::addBullet(const Bullet& bullet) {
    bullets.push_back(bullet);
}

std::vector<Bullet>& EntityManager::getBullets() {
    return bullets;
}

void EntityManager::update(float deltaTime) {
    if (player) player->update(deltaTime);

    for (auto& enemy : enemies) {
        enemy->update(deltaTime);
    }
    std::erase_if(enemies, [](const std::unique_ptr<Enemy>& enemy) { return !enemy->getIsAlive(); });

    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }
    // Сделать пули указателями
    std::erase_if(bullets, [](const Bullet& bullet) { return !bullet.isActive(); });
}

void EntityManager::render(sf::RenderWindow& window) {
    if (player) player->draw(window);

    for (const auto& enemy : enemies) {
        enemy->draw(window);
    }

    for (const auto& bullet : bullets) {
        bullet.draw(window);
    }
}