#pragma once

#include <SFML/Graphics.hpp>

#include "../weapon/Weapon.h"
#include "../../systems/animation/Animation.h"

class Input;

class Player {
   public:
    enum class Direction { None, Up, Down, Left, Right };

    Player(int size, sf::Color color, float speed, int health, int armor, int money);
    void processInput(const Input& inputHandler, float globalTime, std::vector<Bullet>& gameBullets);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    float getX() const;
    float getY() const;
    int getHealth() const;
    int getMoney() const;
    int getArmor() const;
    void takeDamage(int damage);
    void regenerateArmor(float globalTime);
    void takeMoney(int newMoney);
    sf::FloatRect getGlobalBounds() const;
    bool getIsAlive() const;

   private:
    sf::RectangleShape player;
    sf::Sprite sprite;
    Animation animation;
    sf::Vector2f position;
    sf::Vector2f moveDirection;
    sf::Vector2f viewDirection;
    Weapon weapon;
    float speed;
    int health;
    int armor;
    int money;
    bool isAlive;
    float regenerationCooldown;
    float lastRegeneration;

    void processMoveDirection(const Input& inputHandler);
    void processViewDirection(const Input& inputHandler);
    void processShoot(const Input& inputHandler, float globalTime, std::vector<Bullet>& gameBullets);
    void setMoveDirection(const sf::Vector2f& newMoveDirection);
    void setViewDirection(const sf::Vector2f& newViewDirection);
    void view();
    void move(float deltaTime);
};
