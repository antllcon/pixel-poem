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

    // Методы
    std::optional<Bullet> tryShoot(sf::Vector2f position, sf::Vector2f direction, float globalTime);

    // Сеттеры и геттеры
    void setCooldown(float newCooldown);
    float getCooldown() const;
    void setTimeLastShoot(float newTimeLastShoot);
    float getTimeLastShoot() const;

private:
    float cooldown;
    float timeLastShoot = 0.0f;
};
