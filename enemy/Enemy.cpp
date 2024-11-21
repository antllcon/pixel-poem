// Enemy.cpp

#include "Enemy.h"
#include "../config.h"

// Конструктор
Enemy::Enemy(int size, sf::Color color, int health)
	: position(MAP_BOT_SPAWN_X, MAP_BOT_SPAWN_Y), health(health)
{
	enemy.setSize(sf::Vector2f(size, size));
	enemy.setPosition(position);
	enemy.setFillColor(color);
}

void Enemy::draw(sf::RenderWindow &window)
{
	window.draw(enemy);
}

float Enemy::getX() { return position.x; }
float Enemy::getY() { return position.y; }
int Enemy::getHealth() const { return health; }

void Enemy::setX(float x)
{
	position.x = x;
	enemy.setPosition(position);
}

void Enemy::setY(float y)
{
	position.y = y;
	enemy.setPosition(position);
}

void Enemy::setHealth(int newHealth) { health = newHealth; }
