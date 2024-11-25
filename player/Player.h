// player.h

#pragma once

#include <SFML/Graphics.hpp>
#include "../weapon/Weapon.h"

class Input;

class Player
{
public:
    enum class Direction
    {
        None,
        Up,
        Down,
        Left,
        Right
    };

    // Конструктор
    Player(int size, sf::Color color, float speed, int health, bool aim);
    void processInput(const Input& inputHandler, float globalTime);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    // Геттеры и сеттеры
    float getX() const;
    float getY() const;
    float getSpeed() const;
    int getHealth() const;
    bool getAim() const;
    void setX(float newX);
    void setY(float newY);
    void setSpeed(float newSpeed);
    void setHealth(int newHealth);
    void setAim(bool newAim);

private:
    sf::RectangleShape player;
    sf::Vector2f position;
    sf::Vector2f moveDirection;
    sf::Vector2f viewDirection;
    float speed;
    int health;
    bool aim;
    const std::vector<Bullet>& getBullets() const; // Возвращает только для чтения
    std::vector<Bullet>& getBullets(); // Возвращает для модификации

    Weapon weapon;
    std::vector<Bullet> bullets;

    void processMoveDirection(const Input& inputHandler);
    void processViewDirection(const Input& inputHandler);
    void processShoot(const Input& inputHandler, float globalTime);
    void setMoveDirection(const sf::Vector2f& newMoveDirection);
    void setViewDirection(const sf::Vector2f& newViewDirection);
    void view();
    void move(float deltaTime);
    void shoot(float deltaTime);
    void bulletDraw(sf::RenderWindow& window);
};
