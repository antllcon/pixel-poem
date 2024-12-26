#include "UI.h"

#include "../../core/config.h"
#include "../../entities/weapon/Weapon.h"

UI::UI(int maxHealth, int maxArmor, int money, WeaponType weapon) : maxHealth(maxHealth), maxArmor(maxArmor), money(money), weapon(weapon) {
    mapBlock.setSize({BLOCK_SIZE, BLOCK_SIZE});
    font.loadFromFile(SRC_FONT_MONOCRAFT);

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
    armorBarBackground.setOutlineColor(COLOR_BLACK);
    armorBarBackground.setOutlineThickness(UI_OUTLINE);

    armorBar.setSize(BAR_SIZE);
    armorBar.setPosition(ARMOR_BAR_POS);
    armorBar.setFillColor(COLOR_BLUE);

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

    weaponText.setPosition(WEAPON_TEXT_POS);
    weaponText.setFont(font);
    weaponText.setCharacterSize(UI_TEXT);
    weaponText.setFillColor(COLOR_LIGHT_YELLOW);
}

void UI::update(int currentHealth, int currentArmor, int currentMoney, const std::vector<std::vector<int>>& mapGrid, sf::Vector2f playerPosition, sf::Vector2f spawnRoomPosition, sf::Vector2f bossRoomPosition, sf::Vector2f shopRoomPosition) {
    updateHealthBar(currentHealth);
    updateArmorBar(currentArmor);
    updateMoney(currentMoney);
    updateMiniMap(mapGrid);
    updateWeapon(weapon);
    this->spawnRoomPosition = spawnRoomPosition;
    this->bossRoomPosition = bossRoomPosition;
    this->shopRoomPosition = shopRoomPosition;
    this->playerPosition = playerPosition;
}

sf::Color UI::getBlockColor(size_t x, size_t y, int cell) const {
    if (x == static_cast<size_t>(spawnRoomPosition.x / CELL_SIZE) && y == static_cast<size_t>(spawnRoomPosition.y / CELL_SIZE)) {
        return COLOR_WHITE;
    }

    if (x == static_cast<size_t>(bossRoomPosition.x / CELL_SIZE) && y == static_cast<size_t>(bossRoomPosition.y / CELL_SIZE)) {
        return COLOR_BLUE;
    }

    if (x == static_cast<size_t>(shopRoomPosition.x / CELL_SIZE) && y == static_cast<size_t>(shopRoomPosition.y / CELL_SIZE)) {
        return COLOR_GOLD;
    }

    if (x == static_cast<size_t>(playerPosition.x / CELL_SIZE) && y == static_cast<size_t>(playerPosition.y / CELL_SIZE)) {
        return COLOR_GREEN;
    }

    if (cell >= 101 && cell <= 115) {
        return COLOR_PINK;
    }
    if (cell >= 201 && cell <= 211) {
        return COLOR_GRAY;
    }
    return COLOR_DARK;
}

void UI::updateHealthBar(int currentHealth) {
    float healthRatio = static_cast<float>(currentHealth) / maxHealth;
    healthBar.setSize({160.f * healthRatio, 10.f});
    healthText.setString("Health " + std::to_string(currentHealth));
}

void UI::updateArmorBar(int currentArmor) {
    float armorRatio = static_cast<float>(currentArmor) / maxArmor;
    armorBar.setSize({BAR_SIZE.x * armorRatio, BAR_SIZE.y});
    armorText.setString("Armor " + std::to_string(currentArmor));
}

void UI::updateMoney(int currentMoney) { moneyText.setString(std::to_string(currentMoney)); }

void UI::updateWeapon(WeaponType weapon) {
    std::string weaponTexturePath;
    switch (weapon) {
        case WeaponType::Pistol:
            weaponTexturePath = SRC_UI_PISTOL;
            weaponText.setString("Pistol");
            break;
        case WeaponType::Rifle:
            weaponTexturePath = SRC_UI_RIFLE;
            weaponText.setString("Rifle");
            break;
        case WeaponType::Shotgun:
            weaponTexturePath = SRC_UI_SHOTGUN;
            weaponText.setString("Shotgun");
            break;
    }

    weaponTexture.loadFromFile(weaponTexturePath);
    weaponSprite.setTexture(weaponTexture);
    weaponSprite.setScale(SCALE_FACTOR_LEFT);
    weaponSprite.setPosition(WEAPON_SPRITE_POS);
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
    drawMap(window);
}

void UI::drawMap(sf::RenderWindow& window) {
    for (size_t y = 0; y < mapGrid.size(); ++y) {
        for (size_t x = 0; x < mapGrid[y].size(); ++x) {
            int cell = mapGrid[y][x];

            sf::Color blockColor = getBlockColor(x, y, cell);
            mapBlock.setFillColor(blockColor);

            mapBlock.setPosition(x * BLOCK_SIZE + MAP_OFFSET, y * BLOCK_SIZE + MAP_OFFSET);
            window.draw(mapBlock);
        }
    }
}

void UI::updateMiniMap(const std::vector<std::vector<int>>& mapGrid) { this->mapGrid = mapGrid; }