// weapon.h

#pragma once

#include <SFML/Graphics.hpp>
#include "../bullet/bullet.h"
#include <optional>



class Weapon
{
public:
    // Конструктор
    Weapon(float cooldown);

    std::optional<Bullet> shootBullet(sf::Vector2f position, sf::Vector2f direction, float deltaTime);

    // Сеттеры и геттеры
    void setCooldown(float newCooldown);
    float getCooldown();

private:
    float cooldown;
    float timeLastShoot;

    int bulletSize = 5;
    sf::Color bulletColor;
    float bulletSpeed;
    float bulletDamage;
};
