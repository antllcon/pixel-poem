#pragma once
#include "../../entities/entity/EntitiyManager.h"


class MapManager;class CollisionManager {
public:
    CollisionManager();
    ~CollisionManager();

    static void checkCollisions(EntityManager& entityManager, MapManager& mapManager);

private:
    static void checkBulletEnemyCollisions(EntityManager& entityManager);
    static void checkBulletPlayerCollisions(EntityManager& entityManager);
    static void checkPlayerEnemyCollisions(EntityManager& entityManager);
    static void checkEntityWallCollisions(EntityManager& entityManager, MapManager& mapManager);
};
