#include "CollisionManager.h"

#include <iostream>

#include "../../Utils.h"
#include "../../core/config.h"
#include "../map/mapManager.h"

CollisionManager::CollisionManager() = default;
CollisionManager::~CollisionManager() = default;

void CollisionManager::checkCollisions(EntityManager& entityManager, MapManager& mapManager) {
    checkBulletEnemyCollisions(entityManager);
    checkBulletPlayerCollisions(entityManager);
    checkPlayerEnemyCollisions(entityManager);
    // checkEntityWallCollisions(entityManager, mapManager);
}

void CollisionManager::checkBulletEnemyCollisions(EntityManager& entityManager) {
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

void CollisionManager::checkBulletPlayerCollisions(EntityManager& entityManager) {
    for (auto& bullet : entityManager.getBullets()) {
        if (bullet.getOwnerType() == Bullet::OwnerType::Bot) {
            if (bullet.getGlobalBounds().intersects(entityManager.getPlayer()->getGlobalBounds())) {
                entityManager.getPlayer()->takeDamage(bullet.getDamage());
                bullet.setActive(false);
            }
        }
    }
}

void CollisionManager::checkPlayerEnemyCollisions(EntityManager& entityManager) {
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

// void CollisionManager::checkEntityWallCollisions(EntityManager& entityManager, MapManager& mapManager) {
//     // Проверка коллизии игрока со стенами
//     auto player = entityManager.getPlayer();
//     if (player) {
//         sf::Vector2f playerPos = player->getPosition();
//         int gridX = static_cast<int>(playerPos.x / CELL_SIZE);
//         int gridY = static_cast<int>(playerPos.y / CELL_SIZE);
//
//         if (!mapManager.isWalkable(gridX, gridY)) {
//             player->setPosition(player->getPreviousPosition());
//         }
//     }

    // Проверка коллизии врагов со стенами
    // for (auto& enemy : entityManager.getEnemies()) {
    //     sf::Vector2f enemyPos = enemy->getPosition();
    //     int gridX = static_cast<int>(enemyPos.x / CELL_SIZE);
    //     int gridY = static_cast<int>(enemyPos.y / CELL_SIZE);
    //
    //     if (!mapManager.isWalkable(gridX, gridY)) {
    //         enemy->setPosition(enemy->getPreviousPosition()); // Возвращаем врага на предыдущую позицию
    //     }
    // }
// }