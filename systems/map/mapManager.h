#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class MapManager {
public:
    MapManager(int width, int height, int roomCount);
    ~MapManager();

    void generateMap();
    void render(sf::RenderWindow& window);
    // bool isWalkable(int x, int y);
    std::vector<sf::Vector2f> getRoomPositions();
    const Map& getMap() const;

private:
    Map map;
    int roomCount;
};
