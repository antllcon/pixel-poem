#include "Enemy.h"
#include "../config.h"
#include <cmath>

// Конструктор
Enemy::Enemy(int size, sf::Color color, int health)
	: position(MAP_BOT_SPAWN_X, MAP_BOT_SPAWN_Y), health(health) {
	enemy.setSize(sf::Vector2f(size, size));
	enemy.setPosition(position);
	enemy.setFillColor(color);
	setRandomDirection();
}

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(enemy);
}

void Enemy::update(float deltaTime) {
	// Обновляем таймер
	timeSinceDirectionChange += deltaTime;

	// Если пришло время изменить направление
	if (timeSinceDirectionChange >= directionChangeInterval) {
		setRandomDirection();
		timeSinceDirectionChange = 0.f;
	}

	// Двигаем врага
	position += moveDirection * speed * deltaTime;
	enemy.setPosition(position);
}

void Enemy::setRandomDirection() {
	static std::default_random_engine engine(std::random_device{}());
	static std::uniform_real_distribution<float> dist(-1.f, 1.f);

	// Случайное направление
	float x = dist(engine);
	float y = dist(engine);

	float length = std::sqrt(x * x + y * y);
	if (length != 0) {
		moveDirection = sf::Vector2f(x / length, y / length);
	} else {
		moveDirection = sf::Vector2f(0.f, 0.f);
	}
}

// Геттеры и сеттеры
float Enemy::getX() { return position.x; }
float Enemy::getY() { return position.y; }
int Enemy::getHealth() const { return health; }

void Enemy::setX(float x) {
	position.x = x;
	enemy.setPosition(position);
}

void Enemy::setY(float y) {
	position.y = y;
	enemy.setPosition(position);
}

void Enemy::setHealth(int newHealth) { health = newHealth; }
