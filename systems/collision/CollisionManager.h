#pragma once
#include "../../entities/entity/EntityManager.h"


class MapManager;class CollisionManager {
public:
    CollisionManager();
    ~CollisionManager();

    static void checkCollisions(EntityManager& entityManager, MapManager& mapManager);

private:
    static void checkBulletEnemyCollisions(EntityManager& entityManager);
    static void checkBulletPlayerCollisions(EntityManager& entityManager);
    static void checkBulletBossCollisions(EntityManager&entityManager);
    static void checkPlayerEnemyCollisions(EntityManager& entityManager);
    static void checkPlayerBossCollisions(EntityManager&entityManager);
    static void checkPlayerMoneyCollisions(EntityManager& entityManager);
    static void checkPlayerTakeMoneyCollisions(EntityManager& entityManager);
    static void checkEntityWallCollisions(EntityManager& entityManager, MapManager& mapManager);
    static void checkBossWallCollisions(EntityManager&entityManager, MapManager&mapManager);
    static void checkBotWallCollisions(const EntityManager&entityManager, MapManager&mapManager);
    static void checkBulletWallCollisions(EntityManager&entityManager, MapManager&mapManager);
};
