#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../systems/animation/Animation.h"
#include "../weapon/Weapon.h"

class Bullet;
enum class BossState { attack, sleep };

class Boss {
   public:
    Boss(BossState state, sf::Color color, int health, int speed, float directionChangeInterval, float timeScienceDirectionChange, sf::Vector2f position);

    void processInput(sf::Vector2f position, float globalTime, std::vector<Bullet>& gameBullets);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void takeDamage(int damage);
    bool getIsAlive() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setState(BossState newState);
    BossState getState() const;
    void blockMovement();

private:
    sf::Sprite sprite;
    Animation animation;
    sf::RectangleShape boss;
    sf::Vector2f position;
    sf::Vector2f previousPosition;
    sf::Vector2f moveDirection;
    sf::Vector2f viewDirection;
    BossState state;
    Weapon weapon;

    int health;
    int size;
    bool isAlive;
    float speed;
    float directionChangeInterval;
    float timeSinceDirectionChange;


    void processShoot(float globalTime, std::vector<Bullet>& gameBullets, sf::Vector2f playerPosition) ;
    void processViewDirection(sf::Vector2f playerPosition);
    void setViewDirection(const sf::Vector2f& newViewDirection);
    void setRandomDirection();
};