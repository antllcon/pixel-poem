#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Bullet {
public:
    enum class OwnerType { Player, Bot };

    Bullet(OwnerType ownerType, sf::Vector2f position, sf::Vector2f direction, float speed, float damage);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    bool isActive() const;

private:
    OwnerType owner;
    sf::RectangleShape bullet;
    sf::Vector2f direction;
    float speed;
    float damage;
    bool active;
};
