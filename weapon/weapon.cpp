#include "weapon.h"

#include <iostream>

#include "../config.h"

// Конструктор
Weapon::Weapon(float cooldown, int bulletSize, sf::Color bulletColor, float bulletSpeed, float bulletDamage)
    : cooldown(cooldown), timeLastShoot(0.f),
      bulletSize(bulletSize), bulletColor(bulletColor), bulletSpeed(bulletSpeed), bulletDamage(bulletDamage)
{
}

std::optional<Bullet> Weapon::shootBullet(sf::Vector2f position, sf::Vector2f direction, float deltaTime)
{

    timeLastShoot += deltaTime;

    std::cout << cooldown << " <= " << timeLastShoot << std::endl;

    if (0.001f <= timeLastShoot || timeLastShoot == 0.f)
    {
        std::cout << "урон пошел" << std::endl;
        timeLastShoot = 0.f;
        return Bullet(position, direction, 5, BULLET_COLOR, BULLET_SPEED, BULLET_DAMAGE);
    }
    return std::nullopt;
}
