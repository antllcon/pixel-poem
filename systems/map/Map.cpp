
#include "Map.h"

#include <stdint.h>

#include <ctime>
#include <iostream>

#include "../../core/config.h"

Map::Map(int w, int h) : width(w), height(h) { grid.resize(height, std::vector<int>(width, 0)); }

void Map::printMap() const {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::string symbol;
            switch (cell) {
                case 101:
                    symbol = " ▢ ";
                    break;
                case 102:
                    symbol = " ▢ ";
                    break;
                case 103:
                    symbol = " ▢ ";
                    break;
                case 104:
                    symbol = " ▢ ";
                    break;
                case 105:
                    symbol = " ▢ ";
                    break;
                case 106:
                    symbol = " ▢ ";
                    break;
                case 107:
                    symbol = " ▢ ";
                    break;
                case 108:
                    symbol = " ▢ ";
                    break;
                case 109:
                    symbol = " ▢ ";
                    break;
                case 110:
                    symbol = " ▢ ";
                    break;
                case 111:
                    symbol = " ▢ ";
                    break;
                case 112:
                    symbol = " ▢ ";
                    break;
                case 113:
                    symbol = " ▢ ";
                    break;
                case 114:
                    symbol = " ▢ ";
                    break;
                case 115:
                    symbol = " ▢ ";
                    break;

                case 201:
                    symbol = "═╬═";
                    break;
                case 202:
                    symbol = " ╠═";
                    break;
                case 203:
                    symbol = "═╣ ";
                    break;
                case 204:
                    symbol = " ╦ ";
                    break;
                case 205:
                    symbol = " ╩ ";
                    break;
                case 206:
                    symbol = "═══";
                    break;
                case 207:
                    symbol = " ║ ";
                    break;
                case 208:
                    symbol = " ╚═";
                    break;
                case 209:
                    symbol = "═╝ ";
                    break;
                case 210:
                    symbol = " ╔═";
                    break;
                case 211:
                    symbol = "═╗ ";
                    break;
                case 555:
                    symbol = " ▣ ";
                    break;
                case 666:
                    symbol = " X ";
                    break;
                default:
                    symbol = "   ";
                    break;
            }
            std::cout << symbol;
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<int>>& Map::getGrid() { return grid; }

void Map::placeRooms(Map& map, int roomCount) {
    auto& grid = map.getGrid();
    int width = grid[0].size();
    int height = grid.size();

    std::srand(std::time(nullptr));
    for (int i = 0; i < roomCount; ++i) {
        int x, y;
        do {
            // Избегаем крайних рядов и столбцов
            x = ((std::rand() % ((width - 2) / 2)) * 2) + 1;
            y = ((std::rand() % ((height - 2) / 2)) * 2) + 1;

        } while (grid[y][x] != 0);
        grid[y][x] = 1;
    }
}

void Map::connectRooms(Map& map) {
    auto& grid = map.getGrid();
    std::vector<std::pair<int, int>> rooms;

    // Собираем координаты всех комнат
    for (int y = 1; y < grid.size() - 1; ++y) {
        for (int x = 1; x < grid[y].size() - 1; ++x) {
            if (grid[y][x] == 1) rooms.push_back({x, y});
        }
    }

    // Соединяем комнаты коридорами
    for (size_t i = 1; i < rooms.size(); ++i) {
        int x1 = rooms[i - 1].first;
        int y1 = rooms[i - 1].second;
        int x2 = rooms[i].first;
        int y2 = rooms[i].second;

        // Двигаемся к следующей комнате
        while (x1 != x2 || y1 != y2) {
            if (x1 != x2)
                x1 += (x2 > x1) ? 1 : -1;
            else if (y1 != y2)
                y1 += (y2 > y1) ? 1 : -1;

            // Убедимся, что коридоры не выходят за края
            if (x1 > 0 && x1 < grid[0].size() - 1 && y1 > 0 && y1 < grid.size() - 1) {
                if (grid[y1][x1] == 0) grid[y1][x1] = 2;
            }
        }
    }
}

void Map::determinationType() {
    for (int y = 1; y < grid.size() - 1; ++y) {
        for (int x = 1; x < grid[y].size() - 1; ++x) {
            int index = 0;

            int top = grid[y - 1][x];
            int bottom = grid[y + 1][x];
            int left = grid[y][x - 1];
            int right = grid[y][x + 1];

            if (grid[y][x] == 1) {  // Для комнаты
                // 4 выхода
                if (top != 0 && bottom != 0 && left != 0 && right != 0) index = 101;

                // 3 выхода
                if (top != 0 && bottom != 0 && left == 0 && right != 0) index = 102;
                if (top != 0 && bottom != 0 && left != 0 && right == 0) index = 103;
                if (top == 0 && bottom != 0 && left != 0 && right != 0) index = 104;
                if (top != 0 && bottom == 0 && left != 0 && right != 0) index = 105;

                // 2 выхода
                if (top == 0 && bottom == 0 && left != 0 && right != 0) index = 106;
                if (top != 0 && bottom != 0 && left == 0 && right == 0) index = 107;
                if (top != 0 && bottom == 0 && left == 0 && right != 0) index = 108;
                if (top != 0 && bottom == 0 && left != 0 && right == 0) index = 109;
                if (top == 0 && bottom != 0 && left == 0 && right != 0) index = 110;
                if (top == 0 && bottom != 0 && left != 0 && right == 0) index = 111;

                // 1 выход
                if (top == 0 && bottom != 0 && left == 0 && right == 0) index = 112;
                if (top == 0 && bottom == 0 && left == 0 && right != 0) index = 113;
                if (top != 0 && bottom == 0 && left == 0 && right == 0) index = 114;
                if (top == 0 && bottom == 0 && left != 0 && right == 0) index = 115;
            }

            if (grid[y][x] == 2) {  // Для коридора
                // 4 выхода
                if (top != 0 && bottom != 0 && left != 0 && right != 0) index = 201;

                // 3 выхода
                if (top != 0 && bottom != 0 && left == 0 && right != 0) index = 202;
                if (top != 0 && bottom != 0 && left != 0 && right == 0) index = 203;
                if (top == 0 && bottom != 0 && left != 0 && right != 0) index = 204;
                if (top != 0 && bottom == 0 && left != 0 && right != 0) index = 205;

                // 2 выхода
                if (top == 0 && bottom == 0 && left != 0 && right != 0) index = 206;
                if (top != 0 && bottom != 0 && left == 0 && right == 0) index = 207;
                if (top != 0 && bottom == 0 && left == 0 && right != 0) index = 208;
                if (top != 0 && bottom == 0 && left != 0 && right == 0) index = 209;
                if (top == 0 && bottom != 0 && left == 0 && right != 0) index = 210;
                if (top == 0 && bottom != 0 && left != 0 && right == 0) index = 211;
            }

            if (index != 0) {
                grid[y][x] = index;
            }
        }
    }
}

void Map::determinationStartAndEnd() {
    sf::Vector2f startRoomPosition = sf::Vector2f(MAP_WIDTH, MAP_HEIGHT);
    sf::Vector2f endRoomPosition = sf::Vector2f(0, 0);

    for (int y = 1; y < grid.size() - 1; ++y) {
        for (int x = 1; x < grid[y].size() - 1; ++x) {
            if (grid[y][x] / 100 == 1) {
                if (x < startRoomPosition.x || y < startRoomPosition.y) {
                    startRoomPosition.x = x;
                    startRoomPosition.y = y;
                }
                if (x > endRoomPosition.x || y > endRoomPosition.y) {
                    endRoomPosition.x = x;
                    endRoomPosition.y = y;
                }
            }
        }
    }

    grid[endRoomPosition.y][endRoomPosition.x] = 666;
    grid[startRoomPosition.y][startRoomPosition.x] = 555;
}
