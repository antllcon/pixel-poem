#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Bullet
{
public:
    // Конструктор
    Bullet(sf::Vector2f position, sf::Vector2f direction);

    // Методы
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    void activate();
    bool isActive() const;
    void deactivate();

private:
    sf::RectangleShape bullet;
    sf::Vector2f direction;
    float speed;
    float damage;
    bool active;

    void move(float deltaTime);
};
