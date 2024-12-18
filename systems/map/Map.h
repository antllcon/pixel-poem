#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

class Map {
   public:
    Map(int w, int h);

    void printMap() const;
    std::vector<std::vector<int>>& getGrid();
    void determinationType();
    void determinationStartAndEnd();
    static void placeRooms(Map& map, int roomCount);
    static void connectRooms(Map& map);
    sf::Vector2i getStartRoom() const;
    sf::Vector2i getEndRoom() const;

   private:
    sf::Vector2i startRoom;
    sf::Vector2i endRoom;
    int width, height;
    std::vector<std::vector<int>> grid;
};
