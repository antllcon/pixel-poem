#pragma once

#include <SFML/Graphics.hpp>

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
    void processDirection();
    void processFire(float deltaTime);
    void update(float deltaTime);
    void move(float deltaTime);
    void draw(sf::RenderWindow& window);

    // Геттеры и сеттеры
    float getX() const;
    float getY() const;
    float getSpeed() const;
    int getHealth() const;
    bool getAim() const;
    void setX(float x);
    void setY(float y);
    void setSpeed(float newSpeed);
    void setHealth(int newHealth);
    void setAim(bool newAim);
    void setDirection(const sf::Vector2f& newDirection);

private:
    sf::RectangleShape player; // визуальное представление
    sf::Vector2f direction; // направление
    bool aim = false; // авто наведение
    float speed; // скорость
    int health; // здоровье

    void shoot();
    void shootAim();
};
