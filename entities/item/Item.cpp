#include "Item.h"
#include "../../core/config.h"
#include "../../Utils.h"

Item::Item(ItemType type, int cost, sf::Vector2f position)
    : position(position), type(type), cost(cost) {
    // Загрузка текстуры
    switch (type) {
        case ItemType::Weapon:
            texture.loadFromFile(SRC_UI_RIFLE);
        break;
        case ItemType::Armor:
            texture.loadFromFile(SRC_UI_ARMOR);
        break;
        case ItemType::Health:
            texture.loadFromFile(SRC_UI_HEART);
        break;
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(SCALE_FACTOR_LEFT);

    if (!font.loadFromFile(SRC_FONT_MONOCRAFT)) {
        throw std::runtime_error("Failed to load font: " + std::string(SRC_FONT_MONOCRAFT));
    }

    priceText.setFont(font);
    priceText.setString(std::to_string(cost) + "$");
    priceText.setCharacterSize(12);
    priceText.setFillColor(sf::Color::White);
    priceText.setPosition(position.x, position.y - 20);
}

void Item::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(priceText);
}

sf::FloatRect Item::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

ItemType Item::getType() const {
    return type;
}

int Item::getCost() const {
    return cost;
}

void Item::setPosition(float x, float y) {
    position = {x, y};
    sprite.setPosition(position);
    priceText.setPosition(position.x, position.y - 20);
}

sf::Vector2f Item::getPosition() const {
    return position;
}
