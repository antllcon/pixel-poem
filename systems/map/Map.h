#pragma once
#include <vector>

class Map {
   public:
    Map(int w, int h);

    void printMap() const;
    std::vector<std::vector<int>>& getGrid();

    static void placeRooms(Map& map, int roomCount);
    static void connectRooms(Map& map);

   private:
    int width, height;
    std::vector<std::vector<int>> grid;
};
