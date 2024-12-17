
#include "Weapon.h"

#include <unordered_map>

const std::unordered_map<WeaponType, WeaponProperties> weaponConfigs = {
    {WeaponType::Pistol, {2, 0.3f, 600}}, {WeaponType::Rifle, {2, 0.1f, 700}}, {WeaponType::Shotgun, {5, 1.0f, 1000}}};

Weapon::Weapon(WeaponType type) : type(type) {}

std::optional<Bullet> Weapon::tryShoot(sf::Vector2f position, sf::Vector2f direction, float globalTime,
                                       Bullet::OwnerType owner) {
    if (globalTime - timeLastShoot >= getCooldown()) {
        timeLastShoot = globalTime;
        return Bullet(owner, position, direction, getSpeed(), getDamage());
    }
    return std::nullopt;
}

void Weapon::setWeaponType(WeaponType newType) { type = newType; }

WeaponType Weapon::getWeaponType() const { return type; }

float Weapon::getSpeed() const { return weaponConfigs.at(type).speed; }

int Weapon::getDamage() const { return weaponConfigs.at(type).damage; }

float Weapon::getCooldown() const { return weaponConfigs.at(type).cooldown; }