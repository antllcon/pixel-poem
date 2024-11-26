#pragma once
#include <SFML/System/Vector2.hpp>

bool checkCollision(const sf::Vector2f& pos1, const sf::Vector2f& size1,
                    const sf::Vector2f& pos2, const sf::Vector2f& size2) {
    return pos1.x < pos2.x + size2.x &&
           pos1.x + size1.x > pos2.x &&
           pos1.y < pos2.y + size2.y &&
           pos1.y + size1.y > pos2.y;
}
