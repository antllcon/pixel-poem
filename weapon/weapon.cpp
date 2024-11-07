// weapon.cpp

#include "weapon.h"

#include "../config.h"

// Конструктор
Weapon::Weapon(float cooldown)
    : cooldown(cooldown), timeLastShoot(0.f),
      bulletSize(BULLET_SIZE), bulletColor(BULLET_COLOR), bulletSpeed(BULLET_SPEED), bulletDamage(BULLET_DAMAGE)
{
}

std::optional<Bullet> Weapon::shootBullet(sf::Vector2f position, sf::Vector2f direction, float deltaTime)
{
    timeLastShoot += deltaTime;

    if (timeLastShoot >= cooldown)
    {
        timeLastShoot = 0.f;
        return Bullet(position, direction);
    }
    return std::nullopt;
}
