#pragma once

#include "../../systems/animation/Animation.h"


#include <SFML/Graphics.hpp>

#include "../weapon/Weapon.h"

class Bullet;
enum class EnemyState { attack, sleep };

class Enemy {
   public:
    Enemy(EnemyState state, sf::Color color, int health, int speed,
          float directionChangeInterval, float timeSinceDirectionChange);

    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void processInput(sf::Vector2f position, float globalTime,
                      std::vector<Bullet>& gameBullets);
    void takeDamage(int damage);
    bool getIsAlive() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setState(EnemyState newState);
    EnemyState getState() const;

   private:
    sf::Sprite sprite;
    Animation animation;
    sf::RectangleShape enemy;
    sf::Vector2f position;
    sf::Vector2f moveDirection;
    sf::Vector2f viewDirection;
    EnemyState state;
    Weapon weapon;
    int health;
    int size;
    bool isAlive;

    float speed;
    float directionChangeInterval;
    float timeSinceDirectionChange;
    void processShoot(float globalTime, std::vector<Bullet>& gameBullets);
    void processViewDirection(sf::Vector2f playerPosition);
    void setViewDirection(const sf::Vector2f& newViewDirection);
    void setRandomDirection();
};
