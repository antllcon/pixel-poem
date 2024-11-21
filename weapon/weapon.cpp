// weapon.cpp

#include "weapon.h"

// Конструктор
Weapon::Weapon(float cooldown)
{
    this->cooldown = cooldown;
};



// Методы
std::optional<Bullet> Weapon::tryShoot(sf::Vector2f position, sf::Vector2f direction, float globalTime)
{
    if (globalTime - timeLastShoot >= cooldown)
    {
        timeLastShoot = globalTime;
        return Bullet(position, direction);
    }
    return std::nullopt;
}



// Сеттеры и геттеры
void Weapon::setCooldown(float newCooldown) { cooldown = newCooldown; }

float Weapon::getCooldown() const { return cooldown; }

void Weapon::setTimeLastShoot(float newTimeLastShoot) { timeLastShoot = newTimeLastShoot; }

float Weapon::getTimeLastShoot() const { return timeLastShoot; }