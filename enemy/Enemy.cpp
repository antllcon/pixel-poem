#include "Enemy.h"
#include "../config.h"
#include <cmath>
#include <iostream>
#include <random>

// Конструктор
Enemy::Enemy(sf::Color color, int health, int speed, float directionChangeInterval, float timeSinceDirectionChange)
    : position(MAP_BOT_SPAWN_X, MAP_BOT_SPAWN_Y), health(health), size(BOT_SIZE), speed(speed),
      directionChangeInterval(directionChangeInterval),
      timeSinceDirectionChange(timeSinceDirectionChange), isAlive(true) {
    enemy.setPosition(position);
    enemy.setFillColor(color);
    setRandomDirection();
    enemy.setSize(sf::Vector2f(size, size));
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemy);
}

void Enemy::update(float deltaTime) {
    // Обновляем таймер
    timeSinceDirectionChange += deltaTime;

    // Если пришло время изменить направление
    if (timeSinceDirectionChange >= directionChangeInterval) {
        setRandomDirection();
        timeSinceDirectionChange = 0.f;
    }

    // Двигаем врага
    position += moveDirection * speed * deltaTime;
    enemy.setPosition(position);
}

void Enemy::setRandomDirection() {
    static std::default_random_engine engine(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-1.f, 1.f);

    // Случайное направление
    float x = dist(engine);
    float y = dist(engine);

    float length = std::sqrt(x * x + y * y);
    if (length != 0) {
        moveDirection = sf::Vector2f(x / length, y / length);
    }
    else {
        moveDirection = sf::Vector2f(0.f, 0.f);
    }
}

void Enemy::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
}

sf::Vector2f Enemy::getPosition() const {
    return position;
}

void Enemy::takeDamage(float damage) {
    health -= static_cast<int>(damage);
    if (health <= 0 && isAlive) {
        isAlive = false; // Устанавливаем флаг
        std::cout << "Enemy destroyed!" << std::endl;
    }
}


bool Enemy::getIsAlive() const {
    return isAlive;
}