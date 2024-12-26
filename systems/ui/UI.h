#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../../entities/weapon/Weapon.h"
#include "../map/MapManager.h"

class UI {
   public:
    UI(int maxHealth, int maxArmor, int money, WeaponType weapon);
    void update(int currentHealth, int currentArmor, int currentMoney, const std::vector<std::vector<int>> &mapGrid, sf::Vector2f playerPosition, sf::Vector2f spawnRoomPosition, sf::Vector2f bossRoomPosition, sf::Vector2f shopRoomPosition);
    void render(sf::RenderWindow& window);

   private:
    sf::Vector2f spawnRoomPosition;
    sf::Vector2f bossRoomPosition;
    sf::Vector2f shopRoomPosition;
    sf::Vector2f playerPosition;
    sf::Font font;

    sf::Text healthText;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBackground;

    sf::Text armorText;
    sf::RectangleShape armorBar;
    sf::RectangleShape armorBarBackground;

    sf::Text moneyText;
    sf::Texture moneyTexture;
    sf::Sprite moneySprite;

    sf::RectangleShape backgroundPlatform;

    int maxHealth;
    int maxArmor;
    int money;

    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;
    WeaponType weapon;
    sf::Text weaponText;

    std::vector<std::vector<int>> mapGrid;
    sf::RectangleShape mapBlock;

    void updateHealthBar(int currentHealth);
    void updateArmorBar(int currentArmor);
    void updateMoney(int currentMoney);
    void updateWeapon(WeaponType weapon);
    void updateMiniMap(const std::vector<std::vector<int>>& mapGrid);
    sf::Color getBlockColor(size_t x, size_t y, int cell) const;
    void drawMap(sf::RenderWindow& window);
};
