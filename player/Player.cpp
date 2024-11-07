// Player.cpp

#include "Player.h"
#include <cmath>
#include <iostream>

#include "../config.h"

// Конструктор
Player::Player(int size, sf::Color color, float speed, int health, bool aim)
    : moveDirection(0.f, 0.f), speed(speed), health(health), aim(aim), weapon(weapon)
{
    setViewDirection(PLAYER_VIEW);
    player.setSize(sf::Vector2f(size, size * 2));
    player.setFillColor(color);
    player.setPosition(MAP_PLAYER_SPAWN_X, MAP_PLAYER_SPAWN_Y);
    player.setOrigin(size / 2.f, size);
}


// Методы
void Player::processInput(const sf::Event& event, float deltaTime, const sf::RenderWindow& window)
{
    processMoveDirection();
    processViewDirection(window);
    processShoot(event, deltaTime);
}


void Player::update(float deltaTime)
{
    move(deltaTime);
    view();
    shoot(deltaTime);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(player);

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


// Приватные методы
void Player::move(float deltaTime)
{
    const sf::Vector2f offset = moveDirection * speed * deltaTime;
    player.setPosition(player.getPosition().x + offset.x, player.getPosition().y + offset.y);
}

void Player::view()
{
    if (viewDirection.x != 0.f || viewDirection.y != 0.f)
    {
        float angle = std::atan2(viewDirection.y, viewDirection.x) * 180 / M_PI;
        player.setRotation(angle + 90);
    }
}

void Player::shoot(float deltaTime)
{
    for (auto& bullet : bullets)
    {
        bullet.update(deltaTime);
    }

    timeSinceLastShoot += deltaTime;
}


void Player::processViewDirection(const sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f playerPos = player.getPosition();

    sf::Vector2f direction = mousePos - playerPos;

    setViewDirection(direction);
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

void Player::processShoot(const sf::Event& event, float deltaTime)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        std::cout << "курок нажали" << std::endl;
        timeSinceLastShoot += deltaTime;
        std::cout << viewDirection.x << " " << viewDirection.y << std::endl;

        if (timeSinceLastShoot >= shootCooldownTime)
        {
            auto bullet = weapon.shootBullet(player.getPosition(), viewDirection, deltaTime);
            if (bullet.has_value())
            {
                bullets.emplace_back(std::move(bullet.value()));
                std::cout << "выстрел был" << std::endl;
                timeSinceLastShoot = 0.0f;
            }
        }
    }
    else
    {
        timeSinceLastShoot = shootCooldownTime;
    }
}

void Player::setMoveDirection(const sf::Vector2f& newMoveDirection)
{
    moveDirection = newMoveDirection;
}

void Player::setViewDirection(const sf::Vector2f& newViewDirection)
{
    if (newViewDirection.x != 0.f || newViewDirection.y != 0.f)
    {
        float length = std::sqrt(newViewDirection.x * newViewDirection.x + newViewDirection.y * newViewDirection.y);
        viewDirection = sf::Vector2f(newViewDirection.x / length, newViewDirection.y / length);
    }
}
