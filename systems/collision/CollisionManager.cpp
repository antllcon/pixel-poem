#include "CollisionManager.h"

#include <chrono>
#include "../../Utils.h"
#include "../../core/config.h"
#include "../map/MapManager.h"

CollisionManager::CollisionManager() = default;
CollisionManager::~CollisionManager() = default;

void CollisionManager::checkCollisions(EntityManager& entityManager, MapManager& mapManager) {
    checkBulletEnemyCollisions(entityManager);
    checkBulletPlayerCollisions(entityManager);
    checkBulletBossCollisions(entityManager);
    checkPlayerEnemyCollisions(entityManager);
    checkPlayerMoneyCollisions(entityManager);
    checkPlayerTakeMoneyCollisions(entityManager);
    checkEntityWallCollisions(entityManager, mapManager);
    checkBotWallCollisions(entityManager, mapManager);
    checkBulletWallCollisions(entityManager, mapManager);
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

void CollisionManager::checkBulletBossCollisions(EntityManager& entityManager) {
    for (auto& bullet : entityManager.getBullets()) {
        if (bullet.getOwnerType() == Bullet::OwnerType::Player) {
            if (bullet.getGlobalBounds().intersects(entityManager.getBoss()->getGlobalBounds())) {
                entityManager.getBoss()->takeDamage(bullet.getDamage());
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

void CollisionManager::checkPlayerMoneyCollisions(EntityManager& entityManager) {
    for (auto& money : entityManager.getMoneys()) {
        sf::FloatRect viewAreaBounds = money->getGlobalBounds();
        sf::FloatRect viewArea = addFloatRects(viewAreaBounds, MONEY_VIEW_AREA);
        if (entityManager.getPlayer()->getGlobalBounds().intersects(viewArea)) {
            money->setState(MoneyState::take);
        } else {
            if (money->getState() == MoneyState::take) {
                money->setState(MoneyState::lie);
            }
        }
    }
}

void CollisionManager::checkPlayerTakeMoneyCollisions(EntityManager& entityManager) {
    for (auto& money : entityManager.getMoneys()) {
        if (money->getState() == MoneyState::take) {
            if (entityManager.getPlayer()->getGlobalBounds().intersects(money->getGlobalBounds())) {
                money->take(MONEY_VALUE);
                entityManager.getPlayer()->setMoney(MONEY_VALUE);
            }
        }
    }
}

void CollisionManager::checkEntityWallCollisions(EntityManager& entityManager, MapManager& mapManager) {
    auto player = entityManager.getPlayer();
    if (!player) return;

    sf::Vector2f playerPos = player->getPosition();

    float checkPoints[4][2] = {{playerPos.x - ENTITY_SIZE_HALTH, playerPos.y - ENTITY_SIZE_HALTH},
                               {playerPos.x + ENTITY_SIZE_HALTH, playerPos.y - ENTITY_SIZE_HALTH},
                               {playerPos.x - ENTITY_SIZE_HALTH, playerPos.y + ENTITY_SIZE_HALTH},
                               {playerPos.x + ENTITY_SIZE_HALTH, playerPos.y + ENTITY_SIZE_HALTH}};

    for (const auto& point : checkPoints) {
        if (!mapManager.isWalkable(point[0], point[1])) {
            player->blockMovement();
            return;
        }
    }
}

void CollisionManager::checkBossWallCollisions(EntityManager& entityManager, MapManager& mapManager) {
    auto boss = entityManager.getPlayer();
    if (!boss) return;

    sf::Vector2f playerPos = boss->getPosition();

    float checkPoints[4][2] = {{playerPos.x - ENTITY_SIZE_HALTH, playerPos.y - ENTITY_SIZE_HALTH},
                               {playerPos.x + ENTITY_SIZE_HALTH, playerPos.y - ENTITY_SIZE_HALTH},
                               {playerPos.x - ENTITY_SIZE_HALTH, playerPos.y + ENTITY_SIZE_HALTH},
                               {playerPos.x + ENTITY_SIZE_HALTH, playerPos.y + ENTITY_SIZE_HALTH}};

    for (const auto& point : checkPoints) {
        if (!mapManager.isWalkable(point[0], point[1])) {
            boss->blockMovement();
            return;
        }
    }
}

void CollisionManager::checkBotWallCollisions(const EntityManager& entityManager, MapManager& mapManager) {

    for (auto& bot : entityManager.getEnemies()) {
        if (!bot) continue;

        sf::Vector2f botPos = bot->getPosition();

        if (!mapManager.isWalkable(botPos.x, botPos.y)) {
            bot->blockMovement();
            continue;
        }
    }
}

void CollisionManager::checkBulletWallCollisions(EntityManager& entityManager, MapManager& mapManager) {
    for (auto& bullet : entityManager.getBullets()) {
        if (!bullet.isActive()) continue;

        sf::Vector2f bulletPos = bullet.getPosition();

        if (!mapManager.isWalkable(bulletPos.x, bulletPos.y)) {
            bullet.setActive(false);
        }
    }
}
