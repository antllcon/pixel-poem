#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

class Map {
   public:
    Map(int width, int height);

    static void generateRooms(Map& map, int roomCount);
    static void generateCorridors(Map& map);
    void determinationCellTypes();
    void findStartAndEndRooms();
    void setShopRoom();
    std::vector<std::vector<int>>& getGrid();
    sf::Vector2i getSpawnRoomPosition() const;
    sf::Vector2i getBossRoomPosition() const;
    sf::Vector2i getShopRoomPosition()const;
    void printConsole() const;

   private:
    int width, height;
    std::vector<std::vector<int>> grid;
    sf::Vector2i spawnRoom;
    sf::Vector2i bossRoom;
    sf::Vector2i shopRoom;

    sf::Vector2i getRandomRoom(const sf::Vector2i&bossRoom, const sf::Vector2i&playerRoom);
};
