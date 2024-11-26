#include "Bullet.h"
#include "../config.h"

Bullet::Bullet(OwnerType owner, sf::Vector2f position, sf::Vector2f direction, float speed, float damage)
    : owner(owner), direction(direction), speed(speed), damage(damage), active(true) {
    bullet.setSize(sf::Vector2f(BULLET_SIZE, BULLET_SIZE));
    bullet.setFillColor(BULLET_COLOR);
    bullet.setPosition(position);
}

sf::Vector2f Bullet::getPosition() const {
    return bullet.getPosition();
}

bool Bullet::isActive() const {
    return active;
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
