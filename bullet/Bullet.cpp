#include "Bullet.h"
#include "../config.h"

// Конструктор
Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction)
    : direction(direction), speed(BULLET_SPEED), damage(BULLET_DAMAGE), active(true)
{
    bullet.setSize(sf::Vector2f(BULLET_SIZE, BULLET_SIZE));
    bullet.setFillColor(BULLET_COLOR);
    bullet.setPosition(position);
}

// Получить позицию
sf::Vector2f Bullet::getPosition() const {
    return bullet.getPosition();
}

// Получить размер
sf::Vector2f Bullet::getSize() const {
    return bullet.getSize();
}

// Обновить состояние
void Bullet::update(float deltaTime)
{
    if (active) {
        move(deltaTime);
    }
}

// Отрисовать пулю
void Bullet::draw(sf::RenderWindow& window)
{
    if (active) {
        window.draw(bullet);
    }
}

// Движение
void Bullet::move(float deltaTime)
{
    const sf::Vector2f offset = direction * speed * deltaTime;
    bullet.move(offset);
}

// Активация
void Bullet::activate() {
    active = true;
    bullet.setFillColor(BULLET_COLOR); // Визуально сделать видимой
}

// Проверка на активность
bool Bullet::isActive() const {
    return active;
}

// Деактивация
void Bullet::deactivate() {
    active = false;
    bullet.setFillColor(sf::Color::Transparent); // Скрыть пулю
}
