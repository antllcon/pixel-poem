
#include "Map.h";
#include <ctime>
#include <iostream>

Map::Map(int w, int h) : width(w), height(h) {
    grid.resize(height, std::vector<int>(width, 0));
}

void Map::printMap() const {
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell == 0) std::cout << "   "; // Пустое место
            else if (cell == 1) std::cout << " ▢ "; // Комната
            else if (cell == 2) std::cout << " ▫ "; // Коридор
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<int>>& Map::getGrid() { return grid; }

void Map::placeRooms(Map& map, int roomCount){
    auto& grid = map.getGrid();
    int width = grid[0].size();
    int height = grid.size();

    std::srand(std::time(nullptr));
    for (int i = 0; i < roomCount; ++i) {
        int x, y;
        do {
            x = (std::rand() % (width / 2)) * 2;
            y = (std::rand() % (height / 2)) * 2;
        } while (grid[y][x] != 0);
        grid[y][x] = 1;
    }

    if (grid[0][0] != 1) {
        grid[0][0] = 1;
    }
}

void Map::connectRooms(Map& map) {
    auto& grid = map.getGrid();
    std::vector<std::pair<int, int>> rooms;

    // Собираем координаты всех комнат
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 1) rooms.push_back({x, y});
        }
    }

    // Соединяем комнаты коридорами
    for (size_t i = 1; i < rooms.size(); ++i) {
        int x1 = rooms[i - 1].first;
        int y1 = rooms[i - 1].second;
        int x2 = rooms[i].first;
        int y2 = rooms[i].second;

        // Двигаемся к следующей комнате по одному шагу
        while (x1 != x2 || y1 != y2) {
            if (x1 != x2) x1 += (x2 > x1) ? 1 : -1;
            else if (y1 != y2) y1 += (y2 > y1) ? 1 : -1;

            // Если клетка пустая, превращаем её в коридор
            if (grid[y1][x1] == 0) grid[y1][x1] = 2;
        }
    }
}
