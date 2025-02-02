#include "./EntityManager.h"

#include <iostream>

#include "../../core/config.h"
#include "../boss/Boss.h"
#include "../money/Money.h"
#include <random>

EntityManager::EntityManager() = default;
EntityManager::~EntityManager() = default;

void EntityManager::spawnPlayer(const sf::Vector2f& playerRoom) {
    // Исправить player - не передавать size, color
    player = std::make_unique<Player>(PLAYER_SIZE, PLAYER_COLOR, PLAYER_SPEED, PLAYER_HEALTH, PLAYER_ARMOR, PLAYER_MONEY, playerRoom);
}

void EntityManager::spawnBoss(const sf::Vector2f& bossRoom) {
    sf::Vector2f setPosition = {bossRoom.x + CELL_SIZE / 2, bossRoom.y + CELL_SIZE / 2};
    boss = std::make_unique<Boss>(BossState::sleep, BOT_COLOR, BOSS_HEALTH, BOSS_SPEED, BOT_DIRECTION_CHANGE_INTERVAL, BOT_DIRECTION_CHANGE_TIME, setPosition);
}

Player* EntityManager::getPlayer() { return player.get(); }

Boss* EntityManager::getBoss() { return boss.get(); }

void EntityManager::spawnEnemies(const std::vector<sf::Vector2f>& roomPositions, const sf::Vector2f& playerRoom) {
    enemies.clear();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dist(1.0f, 3.0f);

    for (int i = 0; i < NUM_ENEMIES; ++i) {
        if (roomPositions.empty()) break;
        sf::Vector2f spawnPosition;
        do {
            int roomIndex = rand() % roomPositions.size();
            spawnPosition = roomPositions[roomIndex];
        } while (spawnPosition == playerRoom);

        sf::Vector2f setPosition = {spawnPosition.x + CELL_SIZE / 2, spawnPosition.y + CELL_SIZE / 2};

        float directionChangeInterval = dist(gen);

        auto enemy = std::make_unique<Enemy>(EnemyState::sleep, BOT_COLOR, BOT_HEALTH, BOT_SPEED, directionChangeInterval, BOT_DIRECTION_CHANGE_TIME, setPosition);
        enemies.push_back(std::move(enemy));
    }
}

void EntityManager::spawnMoney(const std::vector<sf::Vector2f>& roomPositions, const sf::Vector2f& playerRoom) {
    moneys.clear();
    for (int i = 0; i < NUM_MONEY; ++i) {
        if (roomPositions.empty()) break;
        sf::Vector2f spawnPosition;

        do {
            int roomIndex = rand() % roomPositions.size();
            spawnPosition = roomPositions[roomIndex];
        } while (spawnPosition == playerRoom);

        float x = WALL_SIZE + SPAWN_MARGIN + static_cast<float>(rand()) / RAND_MAX * (CELL_SIZE - WALL_SIZE - 2 * SPAWN_MARGIN);
        float y = WALL_SIZE + SPAWN_MARGIN + static_cast<float>(rand()) / RAND_MAX * (CELL_SIZE - WALL_SIZE - 2 * SPAWN_MARGIN);

        sf::Vector2f setPosition = {spawnPosition.x + x, spawnPosition.y + y};

        auto money = std::make_unique<Money>(MoneyState::lie, MONEY_VALUE, MONEY_SPEED, setPosition);
        moneys.push_back(std::move(money));
    }
}


void EntityManager::spawnShopItems(const sf::Vector2f& shopRoom) {
    items.clear();

    constexpr int CENTER_ROOM = CELL_SIZE / 2;

    std::vector<sf::Vector2f> itemPositions = {
        {shopRoom.x + CENTER_ROOM - 60, shopRoom.y + CENTER_ROOM + 40},
        {shopRoom.x + CENTER_ROOM, shopRoom.y + CENTER_ROOM + 40},
        {shopRoom.x + CENTER_ROOM + 60, shopRoom.y + CENTER_ROOM + 40}
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> typeDist(0, 2);
    std::uniform_int_distribution<int> costDist(2, 10);
    std::ranges::shuffle(itemPositions, gen);

    for (const auto& position : itemPositions) {
        ItemType randomType = static_cast<ItemType>(typeDist(gen));
        int randomCost = costDist(gen);
        items.push_back(std::make_unique<Item>(randomType, randomCost, position));
    }
}


const std::vector<std::unique_ptr<Enemy>>& EntityManager::getEnemies() const { return enemies; }

const std::vector<std::unique_ptr<Money>>& EntityManager::getMoneys() const { return moneys; }

std::vector<std::unique_ptr<Item>>& EntityManager::getItems() { return items; }

void EntityManager::addBullet(const Bullet& bullet) { bullets.push_back(bullet); }

std::vector<Bullet>& EntityManager::getBullets() { return bullets; }

void EntityManager::update(float deltaTime) {
    if (player) player->update(deltaTime);

    if (boss) boss->update(deltaTime);
    // if (boss && !boss->getIsAlive()) {
    //     boss.reset();  // Удаляем босса, если он мёртв
    // }

    for (auto& enemy : enemies) {
        enemy->update(deltaTime);
    }
    std::erase_if(enemies, [](const std::unique_ptr<Enemy>& enemy) { return !enemy->getIsAlive(); });

    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }
    // Сделать пули указателями
    std::erase_if(bullets, [](const Bullet& bullet) { return !bullet.isActive(); });

    for (auto& money : moneys) {
        money->update(deltaTime);
    }
    //
    // for (auto& item : items) {
    //     item->update(deltaTime);
    // }
    //
    std::erase_if(moneys, [](const std::unique_ptr<Money>& money) { return !money->getIsTaken(); });
}

void EntityManager::render(sf::RenderWindow& window) {
    for (auto& item : items) {
        if (item) {
            item->draw(window);
        } else {
            std::cerr << "Найдён невалидный предмет!" << std::endl;
        }
    }

    for (const auto& money : moneys) {
        money->draw(window);
    }

    if (player) player->draw(window);

    for (const auto& enemy : enemies) {
        enemy->draw(window);
    }

    for (const auto& bullet : bullets) {
        bullet.draw(window);
    }

    if (boss && boss->getIsAlive()) boss->draw(window);
}