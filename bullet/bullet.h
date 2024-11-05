#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Bullet
{
public:
    // Конструктор
    Bullet(sf::Vector2f position, sf::Vector2f direction, int size, sf::Color color, float speed, float damage);

    // Методы
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    // Сеттеры и геттеры
    void setX(float newX);
    void setY(float newY);
    void setSpeed(float newSpeed);
    void setDamage(float newDamage);
    void setDirection(sf::Vector2f newDirection);
    float getX() const;
    float getY() const;
    float getSpeed() const;
    float getDamage() const;
    sf::Vector2f getDirection() const;

private:
    sf::RectangleShape bullet;

    sf::Vector2f direction;
    sf::Color color;
    float speed;
    float damage;


    void move(float deltaTime);
};
