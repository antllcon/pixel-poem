#include "UI.h"

#include <iostream>

#include "../../core/config.h"
#include "../../entities/weapon/Weapon.h"

UI::UI(int maxHealth, int maxArmor, int money, WeaponType weapon) : maxHealth(maxHealth), maxArmor(maxArmor), money(money), weapon(weapon), blockSize(16.f) {
    mapBlock.setSize({blockSize, blockSize});
    if (!font.loadFromFile(SRC_FONT_MONOCRAFT)) {
        throw std::runtime_error("Failed to load font from " + std::string(SRC_FONT_MONOCRAFT));
    }

    backgroundPlatform.setSize(BACKGROUND_PLATFORM_SIZE);
    backgroundPlatform.setPosition(BACKGROUND_PLATFORM_POS);
    backgroundPlatform.setFillColor(COLOR_DARK);
    backgroundPlatform.setOutlineColor(COLOR_BLACK);
    backgroundPlatform.setOutlineThickness(UI_OUTLINE);

    healthBarBackground.setSize(BAR_SIZE);
    healthBarBackground.setFillColor(COLOR_GRAY);
    healthBarBackground.setPosition(HEALTH_BACKGROUND_POS);

    healthBar.setSize(BAR_SIZE);
    healthBar.setPosition(HEALTH_BAR_POS);
    healthBar.setFillColor(COLOR_RED);
    healthBarBackground.setOutlineColor(COLOR_BLACK);
    healthBarBackground.setOutlineThickness(UI_OUTLINE);

    healthText.setPosition(HEALTH_TEXT_POS);
    healthText.setFont(font);
    healthText.setCharacterSize(UI_TEXT);
    healthText.setFillColor(COLOR_LIGHT_YELLOW);

    armorBarBackground.setSize(BAR_SIZE);
    armorBarBackground.setPosition(ARMOR_BACKGROUND_POS);
    armorBarBackground.setFillColor(COLOR_GRAY);

    armorBar.setSize(BAR_SIZE);
    armorBar.setPosition(ARMOR_BAR_POS);
    armorBar.setFillColor(COLOR_BLUE);
    armorBarBackground.setOutlineColor(COLOR_BLACK);
    armorBarBackground.setOutlineThickness(UI_OUTLINE);

    armorText.setPosition(ARMOR_TEXT_POS);
    armorText.setFont(font);
    armorText.setCharacterSize(UI_TEXT);
    armorText.setFillColor(COLOR_LIGHT_YELLOW);

    moneyTexture.loadFromFile(SRC_UI_COIN);
    moneySprite.setTexture(moneyTexture);
    moneySprite.setScale(SCALE_FACTOR_LEFT);
    moneySprite.setPosition(MONEY_SPRITE_POS);

    moneyText.setPosition(MONEY_TEXT_POS);
    moneyText.setFont(font);
    moneyText.setCharacterSize(UI_TEXT);
    moneyText.setFillColor(COLOR_LIGHT_YELLOW);

    if (weapon == WeaponType::Pistol) {
        weaponTexture.loadFromFile(SRC_UI_PISTOL);
    }
    if (weapon == WeaponType::Rifle) {
        weaponTexture.loadFromFile(SRC_UI_RIFLE);
    }
    if (weapon == WeaponType::Shotgun) {
        weaponTexture.loadFromFile(SRC_UI_SHOTGUN);
    }
    weaponSprite.setTexture(weaponTexture);
    weaponSprite.setScale(SCALE_FACTOR_LEFT);
    weaponSprite.setPosition(WEAPON_SPRITE_POS);

    weaponText.setPosition(WEAPON_TEXT_POS);
    weaponText.setFont(font);
    weaponText.setCharacterSize(UI_TEXT);
    weaponText.setFillColor(COLOR_LIGHT_YELLOW);
}

void UI::update(int currentHealth, int currentArmor, int currentMoney, WeaponType currentWeapon, std::vector<std::vector<int>> mapGrid) {
    this->mapGrid = mapGrid;

    float healthRatio = static_cast<float>(currentHealth) / maxHealth;
    healthBar.setSize({160.f * healthRatio, 10.f});
    healthText.setString("Health " + std::to_string(currentHealth));

    float armorRatio = static_cast<float>(currentArmor) / maxArmor;
    armorBar.setSize({BAR_SIZE.x * armorRatio, BAR_SIZE.y});
    armorText.setString("Armor " + std::to_string(currentArmor));

    moneyText.setString(std::to_string(currentMoney));

    if (weapon == WeaponType::Pistol) {
        weaponTexture.loadFromFile(SRC_UI_PISTOL);
    }
    if (weapon == WeaponType::Rifle) {
        weaponTexture.loadFromFile(SRC_UI_RIFLE);
    }
    if (weapon == WeaponType::Shotgun) {
        weaponTexture.loadFromFile(SRC_UI_SHOTGUN);
    }
    weaponSprite.setTexture(weaponTexture);
    weaponSprite.setScale(SCALE_FACTOR_LEFT);
    weaponSprite.setPosition(WEAPON_SPRITE_POS);

    std::string weaponTypeText;
    if (weapon == WeaponType::Pistol) {
        weaponTypeText = "Pistol";
    }
    if (weapon == WeaponType::Rifle) {
        weaponTypeText = "Rifle";
    }
    if (weapon == WeaponType::Shotgun) {
        weaponTypeText = "Shotgun";
    }

    weaponText.setString("Gun " + weaponTypeText);
}

void UI::render(sf::RenderWindow& window) {
    window.draw(backgroundPlatform);
    window.draw(healthBarBackground);
    window.draw(healthBar);
    window.draw(healthText);
    window.draw(armorBarBackground);
    window.draw(armorBar);
    window.draw(armorText);
    window.draw(moneySprite);
    window.draw(weaponSprite);
    window.draw(moneyText);
    window.draw(weaponText);
    for (size_t y = 0; y < mapGrid.size(); ++y) {
        for (size_t x = 0; x < mapGrid[y].size(); ++x) {
            int cell = mapGrid[y][x];

            if (cell >= 101 && cell <= 115) {
                mapBlock.setFillColor(COLOR_GOLD);  // Комнаты
            } else if (cell >= 201 && cell <= 211) {
                mapBlock.setFillColor(COLOR_GRAY);  // Туннели
            } else {
                mapBlock.setFillColor(COLOR_DARK);  // Пустота
            }

            mapBlock.setPosition(x * blockSize + MAP_OFFSET, y * blockSize + MAP_OFFSET);
            window.draw(mapBlock);
        }
    }

}