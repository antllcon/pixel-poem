#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class MapManager {
public:
    MapManager(int width, int height, int roomCount);
    ~MapManager();

    void generateMap();
    void render(sf::RenderWindow& window);
    sf::Vector2f getFirstRoomPosition();
    std::vector<sf::Vector2f> getRoomPositions();
    bool isWalkable(int x, int y);
    const Map& getMap() const;

private:
    Map map;
    int roomCount;
};
