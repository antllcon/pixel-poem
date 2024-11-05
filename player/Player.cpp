// Player.cpp

#include "Player.h"
#include "../config.h"

// Конструктор
Player::Player(int size, sf::Color color, float speed, int health, bool aim)
    : moveDirection(0.f, 0.f), speed(speed), health(health), aim(aim), weapon(weapon)
{
    player.setSize(sf::Vector2f(size, size));
    player.setFillColor(color);
    player.setPosition(MAP_PLAYER_SPAWN_X, MAP_PLAYER_SPAWN_Y);
}


// Методы
void Player::update(float deltaTime)
{
    move(deltaTime);
    // Обновляем каждую пулю
    for (auto& bullet : bullets)
    {
        bullet.update(deltaTime);
    }
}

void Player::move(float deltaTime)
{
    const sf::Vector2f offset = moveDirection * speed * deltaTime;
    const sf::Vector2f pos = player.getPosition();
    player.setPosition(pos.x + offset.x, pos.y + offset.y);
}

void Player::processInput(sf::Event event, float deltaTime)
{
    // processShoot(deltaTime);
    processMoveDirection();
    // Проверка стрельбы
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        processShoot(deltaTime);
    }
}

void Player::processShoot(float deltaTime)
{
    auto bullet = weapon.shootBullet(player.getPosition(), moveDirection, deltaTime);
    if (bullet.has_value())
    {
        bullets.emplace_back(std::move(bullet.value()));
    }
}

void Player::processMoveDirection()
{
    sf::Vector2f newDirection(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        newDirection.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        newDirection.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        newDirection.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        newDirection.x += 1;
    }
    setMoveDirection(newDirection);
}

void Player::setMoveDirection(const sf::Vector2f& newMoveDirection)
{
    moveDirection = newMoveDirection;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(player);

    // Отрисовываем каждую пулю
    for (auto& bullet : bullets)
    {
        bullet.draw(window);
    }
}


// Сеттеры и геттеры
void Player::setX(float newX) { player.setPosition(newX, player.getPosition().y); }

void Player::setY(float newY) { player.setPosition(player.getPosition().x, newY); }

void Player::setSpeed(float newSpeed) { speed = newSpeed; }

void Player::setHealth(int newHealth) { health = newHealth; }

void Player::setAim(bool newAim) { aim = newAim; }

float Player::getX() const { return player.getPosition().x; }

float Player::getY() const { return player.getPosition().y; }

float Player::getSpeed() const { return speed; }

int Player::getHealth() const { return health; }

bool Player::getAim() const { return aim; }
