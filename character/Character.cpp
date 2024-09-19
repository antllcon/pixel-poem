#include "Character.hpp"

// Конструктор персонажа
Character::Character(float x, float y, float speed, int health, int armor, int weapon)
    : speed(speed), health(health), armor(armor), weapon(weapon) {
      shape.setSize(sf::Vector2f(20.0f, 20.0f));
      shape.setPosition(x, y);
      shape.setFillColor(sf::Color::Green);
    }

// Функции
void Character::move(float deltaX, float deltaY) {
  shape.move(deltaX * speed, deltaY * speed);
}
void Character::draw(sf::RenderWindow& window) {
  window.draw(shape);
}

// Геттеры для получения значений параметров
int Character::getHealth() const {
  return health;
}
int Character::getArmor() const {
  return armor;
}
int Character::getWeapon() const {
  return weapon;
}

