#include "./mapManager.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../../core/config.h"
#include "Map.h"

MapManager::MapManager(int width, int height, int roomCount)
    : map(width, height), roomCount(roomCount) {}

MapManager::~MapManager() = default;

void MapManager::generateMap() {
    Map::placeRooms(map, roomCount);
    Map::connectRooms(map);
    map.printMap(); // Для отладки
}

void MapManager::render(sf::RenderWindow& window) {
    const auto& grid = map.getGrid();
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 0) continue;

            if (grid[y][x] == 1) cell.setFillColor(COLOR_DARK_PURPLE); // Комната
            else if (grid[y][x] == 2) cell.setFillColor(COLOR_BRAUN); // Коридор

            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            window.draw(cell);
        }
    }
}

const Map& MapManager::getMap() const {
    return map;
}

sf::Vector2f MapManager::getFirstRoomPosition() {
    const auto& grid = map.getGrid();

    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 1) {
                return sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            }
        }
    }

    return sf::Vector2f(0.f, 0.f);
}

bool MapManager::isWalkable(int x, int y) {
    if (x < 0 || x >= map.getGrid()[0].size() || y < 0 || y >= map.getGrid().size()) return false;
    return map.getGrid()[y][x] != 0;
}


std::vector<sf::Vector2f> MapManager::getRoomPositions() {
    std::vector<sf::Vector2f> roomPositions;
    const auto& grid = map.getGrid();

    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 1) {
                roomPositions.emplace_back(x * CELL_SIZE, y * CELL_SIZE);
            }
        }
    }
    return roomPositions;
}

