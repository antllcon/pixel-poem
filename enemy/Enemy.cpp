// Enemy.cpp

#include "Enemy.h"
#include "../config.h"

// Конструктор
Enemy::Enemy(int size, sf::Color color, int health)
	// характеристики
	: health(health)
{
	// визуальное представление
	enemy.setSize(sf::Vector2f(size, size));
	enemy.setPosition(MAP_BOT_SPAWN_X, MAP_BOT_SPAWN_Y);
	enemy.setFillColor(color);
}

// Метод рисования
void Enemy::draw(sf::RenderWindow &window)
{
	window.draw(enemy);
}

// Гетеры
float Enemy::getX() { return enemy.getPosition().x; }
float Enemy::getY() { return enemy.getPosition().y; }

// Геттеры для характеристик
int Enemy::getHealth() const { return health; }

// Cетеры
void Enemy::setX(float x) { enemy.setPosition(x, enemy.getPosition().y); }
void Enemy::setY(float y) { enemy.setPosition(enemy.getPosition().x, y); }

// Сетеры для характеристик
void Enemy::setHealth(int newHealth) { health = newHealth; }
