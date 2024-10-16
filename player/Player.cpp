// Player.cpp

#include "Player.h"
#include "../config.h"

// Конструктор
Player::Player(int size, sf::Color color, float speed, int health)
// характеристики
	: speed(speed), health(health), direction(0.f, 0.f)
{
	// визуальное представление
	player.setSize(sf::Vector2f(size, size));
	player.setPosition(MAP_PLAYER_SPAWN_X, MAP_PLAYER_SPAWN_Y);
	player.setFillColor(color);
}

// Метод обновления игрока (сумма обновлений)
void Player::update(float deltaTime) { move(deltaTime); }

// Метод движения
void Player::move(float deltaTime)
{
	player.move(direction * speed * deltaTime);
}

// Метод обработки клавиатуры
void Player::processInput()
{
	sf::Vector2f newDirection(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		newDirection.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		newDirection.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		newDirection.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		newDirection.x += 1;
	}
	setDirection(newDirection);
}

// Метод рисования
void Player::draw(sf::RenderWindow &window)
{
	window.draw(player);
}

// Гетеры
float Player::getX() { return player.getPosition().x; }
float Player::getY() { return player.getPosition().y; }

// Cетеры
void Player::setDirection(const sf::Vector2f &newDirection)
{
	direction = newDirection;
}

void Player::setX(float x) { player.setPosition(x, player.getPosition().y); }
void Player::setY(float y) { player.setPosition(player.getPosition().x, y); }

// Геттеры для характеристик
float Player::getSpeed() const { return speed; }
int Player::getHealth() const { return health; }

// Сетеры для характеристик
void Player::setSpeed(float newSpeed) { speed = newSpeed; }
void Player::setHealth(int newHealth) { health = newHealth; }
