#pragma once

#include <SFML/Graphics.hpp>

class Bullet;

class Enemy {
   public:
    Enemy(sf::Color color, int health, int speed, float directionChangeInterval,
          float timeSinceDirectionChange);

    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void takeDamage(float damage);
    bool getIsAlive() const;

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

   private:
    sf::RectangleShape enemy;
    sf::Vector2f position;
    sf::Vector2f moveDirection;
    int health;
    int size;
    bool isAlive;

    float speed;
    float directionChangeInterval;
    float timeSinceDirectionChange;

    void setRandomDirection();
};
