
#include "Player.h"

#include <cmath>

#include "../../core/config.h"
#include "../../systems/input/Input.h"

Player::Player(int size, sf::Color color, float speed, int health, int armor, int money)
    : animation(ANIMATION_SPEED),
      position(MAP_PLAYER_SPAWN_X, MAP_PLAYER_SPAWN_Y),
      moveDirection(PLAYER_MOVE_DIRECTION),
      weapon(WeaponType::Rifle),
      speed(speed),
      health(health),
      armor(armor),
      money(money),
      isAlive(true),
      regenerationCooldown(PLAYER_REGENERATION_COOLDOWN) {
    setViewDirection(PLAYER_VIEW);
    player.setSize(sf::Vector2f(size, size));
    player.setFillColor(color);
    player.setPosition(position);
    player.setOrigin(size / 2.f, size / 2.f);

    for (int i = 1; i <= 4; ++i) {
        sf::Texture texture;
        texture.loadFromFile(SRC_KNIGHT + std::to_string(i) + PNG);
        animation.addFrame(texture);
    }

    animation.applyToSprite(sprite);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position);
    sprite.setScale(SCALE_FACTOR_LEFT);
}

void Player::processInput(const Input& inputHandler, float globalTime, std::vector<Bullet>& gameBullets) {
    processViewDirection(inputHandler);
    processMoveDirection(inputHandler);
    processShoot(inputHandler, globalTime, gameBullets);
}

void Player::update(float deltaTime) {
    view();
    move(deltaTime);
    sprite.setPosition(position);
    animation.update(deltaTime);
    animation.applyToSprite(sprite);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player);
    window.draw(sprite);
}

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
        } else {
            newDirection.x = 0.f;
        }
    }

    setViewDirection(newDirection);
    if (newDirection.x > 0) {
        sprite.setScale(SCALE_FACTOR_LEFT);
    } else if (newDirection.x < 0) {
        sprite.setScale(SCALE_FACTOR_RIGHT);
    }
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

void Player::processShoot(const Input& inputHandler, float globalTime, std::vector<Bullet>& gameBullets) {
    if (inputHandler.isPressed("shoot")) {
        auto bulletOpt = weapon.tryShoot(position, viewDirection, globalTime, Bullet::OwnerType::Player);
        if (bulletOpt) {
            gameBullets.push_back(bulletOpt.value());
        }
    }
}

void Player::setMoveDirection(const sf::Vector2f& newMoveDirection) { moveDirection = newMoveDirection; }

void Player::setViewDirection(const sf::Vector2f& newViewDirection) {
    if (newViewDirection.x != 0.f || newViewDirection.y != 0.f) {
        float length = std::sqrt(newViewDirection.x * newViewDirection.x + newViewDirection.y * newViewDirection.y);
        viewDirection = sf::Vector2f(newViewDirection.x / length, newViewDirection.y / length);
    }
}

void Player::move(float deltaTime) {
    previousPosition = position;
    const sf::Vector2f offset = moveDirection * speed * deltaTime;
    position += offset;
    player.setPosition(position);
}

void Player::view() {
    float angle = std::atan2(viewDirection.y, viewDirection.x) * 180 / M_PI;
    player.setRotation(angle + 90);
}

float Player::getX() const { return position.x; }

float Player::getY() const { return position.y; }

int Player::getHealth() const { return health; }

int Player::getArmor() const { return armor; }

int Player::getMoney() const { return money; }

void Player::takeMoney(int newMoney) { money += newMoney; }

sf::FloatRect Player::getGlobalBounds() const { return player.getGlobalBounds(); }

bool Player::getIsAlive() const { return isAlive; }

void Player::takeDamage(int damage) {
    if (armor > 0) {
        armor -= damage;
        if (armor < 0) {
            armor = 0;
        }
    }
    if (armor == 0) {
        if (health > 0) {
            health -= damage;
        }
        if (health == 0 && isAlive) {
            isAlive = false;
        }
    }
}

void Player::regenerateArmor(float globalTime) {
    if (globalTime - lastRegeneration > regenerationCooldown && armor < PLAYER_ARMOR) {
        armor += PLAYER_REGENERATION_ARMOR;
        lastRegeneration = globalTime;
    }
}

sf::Vector2f Player::getPosition() const { return player.getPosition(); }

sf::Vector2f Player::setPosition(sf::Vector2f newPosition) { return position = newPosition; }

// void Player::resolveCollision() {
//     // Корректируем позицию игрока, добавляя откат
//     sf::Vector2f bounce = (previousPosition - position) * COLLISION_BOUNCE_FACTOR;
//     position += bounce;
//
//     // Обновляем положение спрайта
//     player.setPosition(position);
// }
