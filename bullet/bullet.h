// bullet.h

#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../enemy/Enemy.h"

class Bullet
{
public:
    // Конструктор
    Bullet(sf::Vector2f position, sf::Vector2f direction);

    // Методы
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape bullet;
    sf::Vector2f direction;
    sf::Vector2f position;
    sf::Color color;
    float speed;
    float damage;
    int size;
    bool active;

    void move(float deltaTime);
};
