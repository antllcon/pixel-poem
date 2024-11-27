#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Bullet {
public:
    enum class OwnerType { Player, Bot };

    Bullet(OwnerType ownerType, sf::Vector2f position, sf::Vector2f direction, float speed, float damage);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    OwnerType getOwnerType() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    float getDamage() const;
    bool isActive() const;
    void setActive(bool newActive);

private:
    OwnerType owner;
    sf::RectangleShape bullet;
    sf::Vector2f direction;
    float speed;
    float damage;
    bool active;
};
