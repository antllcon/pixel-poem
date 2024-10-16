#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	// Перечисление направления
	enum class Direction
	{
		None,
		Up,
		Down,
		Left,
		Right
	};

	// Конструктор
	Player(int size, sf::Color color, float speed, int health);

	// Методы
	void processInput();
	void update(float deltaTime);
	void move(float deltaTime);
	void draw(sf::RenderWindow& window);

	// Геттеры и сеттеры
	float getX();
	float getY();
	void setDirection(const sf::Vector2f& newDirection);
	float getSpeed() const;
	int getHealth() const;
    void setX(float x);
	void setY(float y);
	void setSpeed(float newSpeed);
	void setHealth(int newHealth);

private:
	sf::RectangleShape player; // визуальное представление
	sf::Vector2f direction;    // направление
	float speed;               // скорость
	int health;                // здоровье
};
