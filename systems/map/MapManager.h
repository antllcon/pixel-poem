#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class MapManager {
public:
    MapManager(int width, int height, int roomCount);
    ~MapManager();

    void generateMap();
    void render(sf::RenderWindow& window);
    sf::Vector2f getPlayerRoomPosition();
    sf::Vector2f getBossRoomPosition();
    std::vector<sf::Vector2f> getRoomPositions();
    std::vector<std::vector<int>>getAllPositions();

    bool isWalkable(int x, int y);
    std::vector<std::vector<int>>& getMap();

private:
    sf::RectangleShape room;
    sf::RectangleShape coridor;
    Map map;
    sf::Sprite sprite;
    sf::Texture texture;
    int roomCount;
    std::vector<std::vector<uint64_t>> walkabilityMasks;

    void precomputeWalkabilityMasks();
    static bool isRoomWalkable(int cellType, float localX, float localY);
    static bool isCorridorWalkable(int cellType, float localX, float localY);
    static bool  isCellWalkable(int cellType, float localX, float localY);
};
