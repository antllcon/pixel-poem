#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../systems/animation/Animation.h"

class Bullet {
public:
    enum class OwnerType { Player, Bot };

    Bullet(OwnerType ownerType, sf::Vector2f positionSpawn, sf::Vector2f direction, float speed, int damage);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    OwnerType getOwnerType() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    int getDamage() const;
    bool isActive() const;
    void setActive(bool newActive);

private:
    OwnerType owner;
    sf::Sprite sprite;
    Animation animation;
    sf::Vector2f position;
    sf::RectangleShape bullet;
    sf::Vector2f direction;
    float speed;
    int damage;
    bool active;
};
