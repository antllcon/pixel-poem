#pragma once
#include "../../entities/EntitiyManager/EntitiyManager.h"

class CollisionManager {
public:
    CollisionManager();
    ~CollisionManager();

    static void checkCollisions(EntityManager& entityManager);

private:
    static void checkBulletEnemyCollisions(EntityManager& entityManager);
    static void checkBulletPlayerCollisions(EntityManager& entityManager);
    static void checkPlayerEnemyCollisions(EntityManager& entityManager);
};
