#pragma once

#include <SFML/Graphics.hpp>

#include "../../systems/animation/Animation.h"
#include "../weapon/Weapon.h"

class Input;

class Player {
   public:
    enum class Direction { None, Up, Down, Left, Right };

    Player(int size, sf::Color color, float speed, int health, int armor, int money, sf::Vector2f position);
    void processInput(const Input& inputHandler, float globalTime, std::vector<Bullet>& gameBullets);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    float getX() const;
    float getY() const;
    int getHealth() const;
    int getMoney() const;WeaponType getWeapon()const;
    int getArmor() const;
    void takeDamage(int damage);
    void regenerateArmor(float globalTime);
    void takeMoney(int newMoney);
    sf::FloatRect getGlobalBounds() const;
    bool getIsAlive() const;
    sf::Vector2f getPosition() const;
    int setMoney(int newMoney);
    void blockMovement();                  // Блокирует движение игрока
    void setMoveDirection(const sf::Vector2f& newMoveDirection);

   private:
    sf::RectangleShape player;
    sf::Sprite sprite;
    Animation animation;
    sf::Vector2f position;
    sf::Vector2f previousPosition;
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
    float timeLastRun = 0.f;
    float timeNextRun = 0.f;

    void processMoveDirection(const Input& inputHandler);
    void processViewDirection(const Input& inputHandler);
    void processShoot(const Input& inputHandler, float globalTime, std::vector<Bullet>& gameBullets);
    void processSpeed(const Input& inputHandler, float globalTime);
    void setViewDirection(const sf::Vector2f& newViewDirection);
    void view();
    void move(float deltaTime);
};
