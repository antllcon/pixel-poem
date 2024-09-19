
#pragma once // включаем это т файл только один раз
#include <SFML/Graphics.hpp>

class Character {
  // Конструктор
  public: Character(
        float x,
        float y,
        float speed,
        int health,
        int armor,
        int weapon
        );

    // Функции
    void move(float dx, float dy);
    void draw(sf::RenderWindow& window);

    // Геттеры для параметров
    int getHealth() const;
    int getArmor() const;
    int getWeapon() const;

    private:
      // Параметры персонажа
      sf::RectangleShape shape;
      float speed;
      int health;
      int armor;
      int weapon;
    };

