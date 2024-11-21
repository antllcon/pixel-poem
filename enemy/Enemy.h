#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Enemy {
public:
	// Конструктор
	Enemy(int size, sf::Color color, int health);

	// Методы
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);

	// Геттеры
	float getX();
	float getY();
	int getHealth() const;

	// Сеттеры
	void setX(float x);
	void setY(float y);
	void setHealth(int newHealth);

private:
	sf::RectangleShape enemy;
	sf::Vector2f position;
	sf::Vector2f moveDirection;
	int health;

	float speed = 100.f;
	float directionChangeInterval = 2.f; // Интервал изменения направления (в секундах)
	float timeSinceDirectionChange = 0.f; // Время с последнего изменения направления

	void setRandomDirection();
};
