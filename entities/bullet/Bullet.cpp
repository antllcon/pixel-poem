#include "Bullet.h"

#include "../../core/config.h"
#include "../player/Player.h"

Bullet::Bullet(OwnerType owner, sf::Vector2f position, sf::Vector2f direction,
               float speed, float damage)
    : owner(owner),
      direction(direction),
      speed(speed),
      damage(damage),
      active(true) {
    bullet.setSize(sf::Vector2f(BULLET_SIZE, BULLET_SIZE));
    if (owner == OwnerType::Player) {
        bullet.setFillColor(BULLET_COLOR);
    }
    if (owner == OwnerType::Bot) {
        bullet.setFillColor(COLOR_RED);
    }
    bullet.setPosition(position);
}

void Bullet::update(float deltaTime) {
    if (active) {
        const sf::Vector2f offset = direction * speed * deltaTime;
        bullet.move(offset);
    }
}

void Bullet::draw(sf::RenderWindow& window) const {
    if (active) {
        window.draw(bullet);
    }
}

Bullet::OwnerType Bullet::getOwnerType() const { return owner; }

sf::Vector2f Bullet::getPosition() const { return bullet.getPosition(); }

sf::FloatRect Bullet::getGlobalBounds() const {
    return bullet.getGlobalBounds();
}

float Bullet::getDamage() const { return damage; }

bool Bullet::isActive() const { return active; }

void Bullet::setActive(bool newActive) { active = newActive; }