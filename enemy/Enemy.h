#pragma once

#include <SFML/Graphics.hpp>

class Enemy {
public:
	// Конструктор
	Enemy(sf::Color color, int health, int speed, float directionChangeInterval, float timeSinceDirectionChange);

	// Методы
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);
	void takeDamage(float damage);
	bool getIsAlive() const;

	// Геттеры
	void setPosition(float x, float y); // Установка позиции
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	int getHealth() const;

	// Сеттеры
	void setHealth(int newHealth);

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
