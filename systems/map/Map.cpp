#include "Map.h"
#include <stdint.h>
#include <ctime>
#include <iostream>
#include "../../core/config.h"

Map::Map(int width, int height): width(width), height(height)
{ grid.resize(height, std::vector<int>(width, 0)); }

void Map::generateRooms(Map& map, int roomCount) {
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

void Map::generateCorridors(Map& map) {
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
            if (rand() % 2 == 0) {
                if (x1 != x2) x1 += (x2 > x1) ? 1 : -1;
            } else {
                if (y1 != y2) y1 += (y2 > y1) ? 1 : -1;
            }

            // Убедимся, что коридоры не выходят за края
            if (x1 > 0 && x1 < grid[0].size() - 1 && y1 > 0 && y1 < grid.size() - 1) {
                if (grid[y1][x1] == 0) grid[y1][x1] = 2;  // 2 — коридор
            }
        }
    }
}

void Map::determinationCellTypes() {
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

void Map::findStartAndEndRooms() {
    spawnRoom = sf::Vector2i(MAP_WIDTH, MAP_HEIGHT);
    bossRoom = sf::Vector2i(0, 0);

    for (int y = 1; y < grid.size() - 1; ++y) {
        for (int x = 1; x < grid[y].size() - 1; ++x) {
            if (grid[y][x] / 100 == 1) {
                if (x < spawnRoom.x || y < spawnRoom.y) {
                    spawnRoom.x = x;
                    spawnRoom.y = y;
                }
                if (x > bossRoom.x || y > bossRoom.y) {
                    bossRoom.x = x;
                    bossRoom.y = y;
                }
            }
        }
    }
}

void Map::setShopRoom() {
    shopRoom = getRandomRoom(spawnRoom, bossRoom);
}

std::vector<std::vector<int>>& Map::getGrid() { return grid; }

sf::Vector2i Map::getSpawnRoomPosition() const {
    sf::Vector2i roomPosition = sf::Vector2i(spawnRoom.x * CELL_SIZE, spawnRoom.y * CELL_SIZE);
    return roomPosition;
}

sf::Vector2i Map::getBossRoomPosition() const {
    sf::Vector2i roomPosition = sf::Vector2i(bossRoom.x * CELL_SIZE, bossRoom.y * CELL_SIZE);
    return roomPosition;
}

sf::Vector2i Map::getShopRoomPosition() const {
    sf::Vector2i roomPosition = sf::Vector2i(shopRoom.x * CELL_SIZE, shopRoom.y * CELL_SIZE);
    return roomPosition;
}

void Map::printConsole() const {
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            std::string symbol;

            if (x == spawnRoom.x && y == spawnRoom.y) {
                symbol = " ▣ ";
            } else if (x == bossRoom.x && y == bossRoom.y) {
                symbol = " X ";
            } else if (x == shopRoom.x && y == shopRoom.y) {
                symbol = " $ ";
            } else {
                switch (grid[y][x]) {
                    case 101:
                    case 102:
                    case 103:
                    case 104:
                    case 105:
                    case 106:
                    case 107:
                    case 108:
                    case 109:
                    case 110:
                    case 111:
                    case 112:
                    case 113:
                    case 114:
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
                        symbol = "═╦═";
                        break;
                    case 205:
                        symbol = "═╩═";
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
                    default:
                        symbol = "   ";
                        break;
                }
            }

            std::cout << symbol;
        }
        std::cout << "\n";
    }
}

sf::Vector2i Map::getRandomRoom(const sf::Vector2i& bossRoom, const sf::Vector2i& playerRoom) {
    int x, y;
    do {
        x = (rand() % (MAP_WIDTH / 2)) * 2 + 1;
        y = (rand() % (MAP_HEIGHT / 2)) * 2 + 1;
    } while ((grid[y][x] < 101 || grid[y][x] > 115) ||
             sf::Vector2i{x, y} == bossRoom ||
             sf::Vector2i{x, y} == playerRoom);
    return sf::Vector2i{x, y};
}
