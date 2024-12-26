#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

enum class ItemType { Weapon, Armor, Health };

class Item {
public:
    Item(ItemType type, int cost, sf::Vector2f position);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds() const;
    ItemType getType() const;
    int getCost() const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text priceText;
    sf::Vector2f position;
    ItemType type;
    int cost;
};
