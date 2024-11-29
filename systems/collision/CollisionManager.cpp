#include "CollisionManager.h"
#include "../../Utils.h"
#include "../../core/config.h"

CollisionManager::CollisionManager() = default;
CollisionManager::~CollisionManager() = default;

void CollisionManager::checkCollisions(EntityManager& entityManager) {
    checkBulletEnemyCollisions(entityManager);
    checkBulletPlayerCollisions(entityManager);
    checkPlayerEnemyCollisions(entityManager);
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
