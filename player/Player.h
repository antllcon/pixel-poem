#pragma once

#include <SFML/Graphics.hpp>
#include "../weapon/weapon.h"

class Player
{
public:
    // Перечисление направления
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

    // Методы
    void processInput(sf::Event event, float deltaTime);
    void processMoveDirection();
    void processShoot(float deltaTime);
    void update(float deltaTime);
    void move(float deltaTime);
    void shoot(float deltaTime);
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
    void setMoveDirection(const sf::Vector2f& newMoveDirection);

private:
    sf::RectangleShape player; // визуальное представление
    sf::Vector2f moveDirection; // направление ходьбы
    // TODO сделать направление взгляда
    sf::Vector2f lastDirection; // последнее направление
    // sf::Vector2f shootDirection; // направление стрельбы
    float speed; // скорость
    int health; // здоровье
    bool aim; // авто наведение

    // TODO придумать как прокинуть константу
    Weapon weapon;
    std::vector<Bullet> bullets;

    void handleShoot(float deltaTime);
};
