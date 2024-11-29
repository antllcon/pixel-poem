#pragma once
#include <memory>
#include <vector>

#include "../../entities/bullet/Bullet.h"
#include "../../entities/enemy/Enemy.h"
#include "../../entities/player/Player.h"

class EntityManager {
   public:
    EntityManager();
    ~EntityManager();

    void spawnPlayer();
    Player* getPlayer();

    void spawnEnemies();
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() const;

    void addBullet(const Bullet& bullet);
    std::vector<Bullet>& getBullets();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

   private:
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Bullet> bullets;
};
