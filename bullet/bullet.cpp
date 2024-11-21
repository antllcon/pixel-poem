// bullet.cpp

#include "bullet.h"
#include "../config.h"
#include "../enemy/Enemy.h"


// Конструктор
Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction)
    : direction(direction), speed(BULLET_SPEED), damage(BULLET_DAMAGE), size(BULLET_SIZE), active(false)
{
    bullet.setSize(sf::Vector2f(size, size));
    bullet.setFillColor(BULLET_COLOR);
    bullet.setPosition(position);
}

// Методы
void Bullet::update(float deltaTime)
{
    move(deltaTime);
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(bullet);
}

void Bullet::move(float deltaTime)
{
    const sf::Vector2f offset = direction * speed * deltaTime;
    const sf::Vector2f pos = bullet.getPosition();
    bullet.setPosition(pos.x + offset.x, pos. y + offset.y);
}
