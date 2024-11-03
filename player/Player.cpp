// Player.cpp

#include "Player.h"
#include "../config.h"

// Конструктор
Player::Player(int size, sf::Color color, float speed, int health, bool aim)
    : direction(0.f, 0.f), aim(aim), speed(speed), health(health)
{
    player.setSize(sf::Vector2f(size, size));
    player.setFillColor(color);
    player.setPosition(MAP_PLAYER_SPAWN_X, MAP_PLAYER_SPAWN_Y);
}

// Методы
void Player::update(float deltaTime) { move(deltaTime); }

void Player::move(float deltaTime)
{
    player.move(direction * speed * deltaTime);
}

void Player::processInput(sf::Event event, float deltaTime)
{
    processFire(deltaTime);
    processDirection();
}

void Player::processFire(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (aim)
        {
            // shootAim();
        }
        else
        {
            // shoot();
        }
    }
}

void Player::processDirection()
{
    sf::Vector2f newDirection(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        newDirection.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        newDirection.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        newDirection.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        newDirection.x += 1;
    }
    setDirection(newDirection);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(player);
}

// Геттеры и сеттеры
float Player::getX() const { return player.getPosition().x; }
float Player::getY() const { return player.getPosition().y; }

void Player::setDirection(const sf::Vector2f& newDirection)
{
    direction = newDirection;
}

void Player::setX(float x) { player.setPosition(x, player.getPosition().y); }
void Player::setY(float y) { player.setPosition(player.getPosition().x, y); }

// Геттеры для характеристик
float Player::getSpeed() const { return speed; }
int Player::getHealth() const { return health; }
bool Player::getAim() const { return aim; }

// Сетеры для характеристик
void Player::setSpeed(float newSpeed) { speed = newSpeed; }
void Player::setHealth(int newHealth) { health = newHealth; }

void Player::setAim(bool newAim) { aim = newAim; }
