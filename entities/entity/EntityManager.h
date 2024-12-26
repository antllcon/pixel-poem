#pragma once
#include <memory>
#include <vector>

#include "../../entities/bullet/Bullet.h"
#include "../../entities/enemy/Enemy.h"
#include "../../entities/player/Player.h"
#include "../../entities/money/Money.h"
#include "../../entities/boss/Boss.h"
#include "../item/Item.h"

class EntityManager {
   public:
    EntityManager();
    ~EntityManager();

    void spawnPlayer(const sf::Vector2f& playerRoom);
    void spawnBoss(const sf::Vector2f&bossRoom);
    Player* getPlayer();
    Boss* getBoss();

    void spawnEnemies(const std::vector<sf::Vector2f>& roomPositions, const sf::Vector2f& playerRoom);
    void spawnMoney(const std::vector<sf::Vector2f>& roomPositions, const sf::Vector2f& playerRoom);
    void spawnShopItems(const sf::Vector2f&shopRoom);

    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const;
    const std::vector<std::unique_ptr<Money>>& getMoneys() const;
    std::vector<std::unique_ptr<Item>>& getItems();

    void addBullet(const Bullet& bullet);
    std::vector<Bullet>& getBullets();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

   private:
    std::unique_ptr<Player> player;
    std::unique_ptr<Boss> boss;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Bullet> bullets;
    std::vector<std::unique_ptr<Money>> moneys;
    std::vector<std::unique_ptr<Item>> items;
};
