#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	// Конструктор
	Enemy(int size, sf::Color color, int health);

	// Методы
	void draw(sf::RenderWindow &window);

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
	int health;
};
