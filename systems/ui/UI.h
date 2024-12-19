#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../../entities/weapon/Weapon.h"

class UI {
   public:
    UI(int maxHealth, int maxArmor, int money, WeaponType weapon);
    void update(int currentHealth, int currentArmor, int currentMoney, WeaponType currentWeapon);
    void render(sf::RenderWindow& window);

   private:
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


};
