#include "Money.h"

#include <iostream>
#include <random>

#include "../../Utils.h"
#include "../../core/config.h"

Money::Money(MoneyState state, int moneyValue, int speed, sf::Vector2f position)
    : animation(ANIMATION_SPEED),
      position(position),
      state(state),
      moneyValue(moneyValue),
      size(MONEY_SIZE),
      isTaken(true),
      speed(speed) {
    enemy.setSize(sf::Vector2f(size, size));
    enemy.setOrigin(enemy.getLocalBounds().width / 2, enemy.getLocalBounds().height / 2);

    for (int i = 1; i <= 4; ++i) {
        sf::Texture texture;
        texture.loadFromFile(SRC_COIN + std::to_string(i) + PNG);
        animation.addFrame(texture);
    }

    animation.applyToSprite(sprite);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position);
    sprite.setScale(SCALE_FACTOR_LEFT);
}

void Money::draw(sf::RenderWindow& window) { window.draw(sprite); }

void Money::update(float deltaTime) {
    if (state == MoneyState::take) {
        // Нормализуем направление перед движением
        sf::Vector2f normalizedDirection = viewDirection;
        float length = std::sqrt(normalizedDirection.x * normalizedDirection.x + normalizedDirection.y * normalizedDirection.y);
        if (length != 0) {
            normalizedDirection /= length;
        }
        position += normalizedDirection * speed * deltaTime;
    }
    enemy.setPosition(position);
    sprite.setPosition(position);
    animation.update(deltaTime);
    animation.applyToSprite(sprite);
}

void Money::processInput(sf::Vector2f playerPosition) {
    processViewDirection(playerPosition);
}

void Money::processViewDirection(sf::Vector2f playerPosition) {
    sf::Vector2f newViewDirection = playerPosition - position;
    setViewDirection(newViewDirection);
}

void Money::setPosition(float x, float y) { position = sf::Vector2f(x, y); }

sf::Vector2f Money::getPosition() const { return position; }

void Money::take(int damage) {
    moneyValue -= damage;
    if (moneyValue <= 0 && isTaken) {
        isTaken = false;
    }
}

bool Money::getIsTaken() const { return isTaken; }

sf::FloatRect Money::getGlobalBounds() const { return enemy.getGlobalBounds(); }

void Money::setViewDirection(const sf::Vector2f& newViewDirection) { viewDirection = newViewDirection; }

MoneyState Money::getState() const { return state; }

void Money::setState(MoneyState newState) { state = newState; }
