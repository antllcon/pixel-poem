// Weapon.h

#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

#include "../bullet/Bullet.h"

struct WeaponProperties {
    float damage;
    float cooldown;
    float speed;
};

enum class WeaponType { Pistol, Rifle, Shotgun };

class Weapon {
   public:
    Weapon(WeaponType type);
    std::optional<Bullet> tryShoot(sf::Vector2f vector2, sf::Vector2f direction,
                                   float global_time, Bullet::OwnerType owner);
    void setWeaponType(WeaponType newType);
    float getSpeed() const;
    float getDamage() const;
    float getCooldown() const;
    WeaponType getWeaponType() const;

   private:
    WeaponType type;
    float timeLastShoot = 0.0f;
};
