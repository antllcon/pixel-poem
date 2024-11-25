// Player.cpp

#include "Player.h"
#include <cmath>

#include "../config.h"
#include "../input/Input.h"

// Конструктор
Player::Player(int size, sf::Color color, float speed, int health, bool aim)
    : position(MAP_PLAYER_SPAWN_X, MAP_PLAYER_SPAWN_Y), moveDirection(0.f, 0.f), speed(speed), health(health), aim(aim),
      weapon(WEAPON_COOLDOWN) {
    setViewDirection(PLAYER_VIEW);
    player.setSize(sf::Vector2f(size, size));
    player.setFillColor(color);
    player.setPosition(position);
    player.setOrigin(size / 2.f, size / 2.f);
}

// Методы
void Player::processInput(const Input& inputHandler, float globalTime) {
    processViewDirection(inputHandler);
    processMoveDirection(inputHandler);
    processShoot(inputHandler, globalTime);
}

void Player::update(float deltaTime) {
    view();
    move(deltaTime);
    shoot(deltaTime);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player);
    bulletDraw(window);
}


// Приватные методы
void Player::processViewDirection(const Input& inputHandler) {
    sf::Vector2f newDirection(0.f, 0.f);
    if (inputHandler.isPressed("lookUp")) {
        newDirection.y -= 1;
    }
    if (inputHandler.isPressed("lookDown")) {
        newDirection.y += 1;
    }
    if (inputHandler.isPressed("lookLeft")) {
        newDirection.x -= 1;
    }
    if (inputHandler.isPressed("lookRight")) {
        newDirection.x += 1;
    }
    if (newDirection.x != 0.f && newDirection.y != 0.f) {
        if (std::abs(newDirection.x) > std::abs(newDirection.y)) {
            newDirection.y = 0.f;
        }
        else {
            newDirection.x = 0.f;
        }
    }
    setViewDirection(newDirection);
}

void Player::processMoveDirection(const Input& inputHandler) {
    sf::Vector2f newDirection(0.f, 0.f);
    if (inputHandler.isPressed("moveUp")) {
        newDirection.y -= 1;
    }
    if (inputHandler.isPressed("moveDown")) {
        newDirection.y += 1;
    }
    if (inputHandler.isPressed("moveLeft")) {
        newDirection.x -= 1;
    }
    if (inputHandler.isPressed("moveRight")) {
        newDirection.x += 1;
    }
    setMoveDirection(newDirection);
}

void Player::processShoot(const Input& inputHandler, float globalTime) {
    if (inputHandler.isPressed("shoot")) {
        auto bulletOpt = weapon.tryShoot(position, viewDirection, globalTime);
        if (bulletOpt) {
            bullets.push_back(bulletOpt.value());
        }
    }
}

void Player::setMoveDirection(const sf::Vector2f& newMoveDirection) {
    moveDirection = newMoveDirection;
}

void Player::setViewDirection(const sf::Vector2f& newViewDirection) {
    if (newViewDirection.x != 0.f || newViewDirection.y != 0.f) {
        float length = std::sqrt(newViewDirection.x * newViewDirection.x + newViewDirection.y * newViewDirection.y);
        viewDirection = sf::Vector2f(newViewDirection.x / length, newViewDirection.y / length);
    }
}

void Player::move(float deltaTime) {
    const sf::Vector2f offset = moveDirection * speed * deltaTime;
    position += offset;
    player.setPosition(position);
}

void Player::view() {
    float angle = std::atan2(viewDirection.y, viewDirection.x) * 180 / M_PI;
    player.setRotation(angle + 90);
}

void Player::shoot(float deltaTime) {
    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }
}

void Player::bulletDraw(sf::RenderWindow& window) {
    for (auto& bullet : bullets) {
        bullet.draw(window);
    }
}

// Сеттеры и геттеры
void Player::setX(float newX) {
    position.x = newX;
    player.setPosition(position);
}

void Player::setY(float newY) {
    position.y = newY;
    player.setPosition(position);
}

void Player::setSpeed(float newSpeed) { speed = newSpeed; }

void Player::setHealth(int newHealth) { health = newHealth; }

void Player::setAim(bool newAim) { aim = newAim; }

float Player::getX() const { return position.x; }

float Player::getY() const { return position.y; }

float Player::getSpeed() const { return speed; }

int Player::getHealth() const { return health; }

bool Player::getAim() const { return aim; }

const std::vector<Bullet>& Player::getBullets() const {
    return bullets;
}

std::vector<Bullet>& Player::getBullets() {
    return bullets;
}
