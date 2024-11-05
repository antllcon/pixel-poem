// bullet.cpp

#include "bullet.h"

// Конструктор
Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, int size, sf::Color color, float speed, float damage)
    : direction(direction), color(color), speed(speed), damage(damage)
{
    bullet.setSize(sf::Vector2f(size, size));
    bullet.setFillColor(color);
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



// Сеттеры и геттеры
void Bullet::setX(float newX) { bullet.setPosition(newX, bullet.getPosition().y); }

void Bullet::setY(float newY) { bullet.setPosition(bullet.getPosition().x, newY); }

void Bullet::setSpeed(float newSpeed) { speed = newSpeed; }

void Bullet::setDamage(float newDamage) { damage = newDamage; }

void Bullet::setDirection(sf::Vector2f newDirection) { direction = newDirection; }

float Bullet::getX() const { return bullet.getPosition().x; }

float Bullet::getY() const { return bullet.getPosition().y; }

float Bullet::getSpeed() const { return speed; }

float Bullet::getDamage() const { return damage; }

sf::Vector2f Bullet::getDirection() const
{
    return direction;
}

