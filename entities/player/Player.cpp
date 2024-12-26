
#include "Player.h"

#include <cmath>

#include "../../core/config.h"
#include "../../systems/input/Input.h"

Player::Player(int size, sf::Color color, float speed, int health, int armor, int money, sf::Vector2f position)
    : animation(ANIMATION_SPEED),
      position(position.x + CELL_SIZE / 2, position.y + CELL_SIZE / 2),
      moveDirection(PLAYER_MOVE_DIRECTION),
      weapon(WeaponType::Pistol),
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
    processSpeed(inputHandler, globalTime);
}

void Player::update(float deltaTime) {
    view();
    move(deltaTime);
    sprite.setPosition(position);
    animation.update(deltaTime);
    animation.applyToSprite(sprite);
}

void Player::draw(sf::RenderWindow& window) { window.draw(sprite); }

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
void Player::processSpeed(const Input& inputHandler, float globalTime) {
    // Проверяем, можно ли бежать
    if (inputHandler.isPressed("run") && globalTime >= timeNextRun) {
        speed = PLAYER_SPEED * 2; // Удваиваем скорость
        timeLastRun = globalTime; // Запоминаем момент начала бега
        timeNextRun = globalTime + RUN_COOLDOWN; // Устанавливаем задержку на следующее ускорение
    } else if (globalTime - timeLastRun >= PLAYER_RUN_TIME) {
        speed = PLAYER_SPEED; // Возвращаемся к обычной скорости
    }

    // std::cout << " Время: " << globalTime - timeLastRun << std::endl;
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

WeaponType Player::getWeapon() const {return weapon.getWeaponType(); }

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

WeaponType Player::swapWeapon(WeaponType newWeapon) {
    WeaponType oldWeapon = weapon.getWeaponType();
    weapon = newWeapon;
    return oldWeapon; // Возвращаем старое оружие
}

void Player::restoreArmor() {
    armor = PLAYER_ARMOR; // PLAYER_ARMOR — максимальная броня
}

void Player::restoreHealth() {
    health = PLAYER_HEALTH; // PLAYER_HEALTH — максимальное здоровье
}

bool Player::reduceMoney(int amount) {
    if (money >= amount) {
        money -= amount;
        return true; // Покупка прошла успешно
    }
    return false; // Недостаточно денег
}


sf::Vector2f Player::getPosition() const { return player.getPosition(); }

int Player::setMoney(int newMoney) { return money += newMoney; }

void Player::blockMovement() {
    position = previousPosition;
    player.setPosition(position);
}
