#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "../../systems/animation/Animation.h"

enum class MoneyState { take, lie };

class Money {
   public:
    Money(MoneyState state, int moneyValue, int speed, sf::Vector2f position);

    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void processInput(sf::Vector2f position);
    void take(int damage);
    bool getIsTaken() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setState(MoneyState newState);
    MoneyState getState() const;

   private:
    sf::Sprite sprite;
    Animation animation;
    sf::RectangleShape enemy;
    sf::Vector2f position;
    sf::Vector2f moveDirection;
    sf::Vector2f viewDirection;
    MoneyState state;
    int moneyValue;
    int size;
    bool isTaken;

    float speed;
    void processViewDirection(sf::Vector2f playerPosition);
    void setViewDirection(const sf::Vector2f& newViewDirection);
};
