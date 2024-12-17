#include "./MapManager.h"

#include <bitset>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

#include "../../core/config.h"
#include "Map.h"

MapManager::MapManager(int width, int height, int roomCount) : map(width, height), roomCount(roomCount) {
    sf::Vector2f size = sf::Vector2f(CELL_SIZE, CELL_SIZE);
    room.setSize(size);
    coridor.setSize(size);
}


MapManager::~MapManager() = default;



void MapManager::generateMap() {
    std::cout << " Генерация комнат " << std::endl;
    Map::placeRooms(map, roomCount);
    std::cout << " Генерация туннелей " << std::endl;
    Map::connectRooms(map);
    std::cout << " Распределение типов комнат " << std::endl;
    map.determinationType();
    std::cout << " Установка появления игрока и босса " << std::endl;
    map.determinationStartAndEnd();
    std::cout << " Установка текстур или раскраска " << std::endl;
    precomputeWalkabilityMasks();
    map.printMap();
}






void MapManager::render(sf::RenderWindow& window) {
    const auto& grid = map.getGrid();
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 0) {
                continue;
            }
            if (grid[y][x] != 0) {
                room.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            }
            if (grid[y][x] / 100 == 1) {
                texture.loadFromFile(SRC_ROOM + std::to_string(grid[y][x]) + PNG);
                sprite.setTexture(texture);
                sprite.setScale(SCALE_FACTOR);
                window.draw(sprite);
            }
            if (grid[y][x] / 100 == 2) {
                texture.loadFromFile(SRC_TRANSITION + std::to_string(grid[y][x]) + PNG);
                sprite.setScale(SCALE_FACTOR);
                window.draw(sprite);
            }
        }
    }
}






std::vector<std::vector<int>>& MapManager::getMap() { return map.getGrid(); }






sf::Vector2f MapManager::getPlayerRoomPosition() {
    const auto& grid = map.getGrid();
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 555) {
                return sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            }
        }
    }
    return sf::Vector2f(0.f, 0.f);
}


sf::Vector2f MapManager::getBossRoomPosition() {
    const auto& grid = map.getGrid();
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 666) {
                return sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            }
        }
    }
    return sf::Vector2f(0.f, 0.f);
}




std::vector<sf::Vector2f> MapManager::getRoomPositions() {
    std::vector<sf::Vector2f> roomPositions;
    const auto& grid = map.getGrid();

    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] / 100 == 1) {
                roomPositions.emplace_back(x * CELL_SIZE, y * CELL_SIZE);
            }
        }
    }
    return roomPositions;
}





std::vector<std::vector<int>> MapManager::getAllPositions() {
    std::vector<sf::Vector2f> roomPositions;
    return map.getGrid();
}




bool MapManager::isWalkable(int x, int y) {
    int cellX = x / CELL_SIZE;
    int cellY = y / CELL_SIZE;

    if (cellX < 0 || cellX >= MAP_WIDTH || cellY < 0 || cellY >= MAP_HEIGHT) {
        return false;
    }

    int numDivisions = 8; // Соответствует 8x8 разбиению
    int subCellSize = CELL_SIZE / numDivisions;
    int localX = (x % CELL_SIZE) / subCellSize;
    int localY = (y % CELL_SIZE) / subCellSize;
    int bitIndex = localY * numDivisions + localX;

    return walkabilityMasks[cellY][cellX] & (uint64_t(1) << bitIndex);
}



bool MapManager::isRoomWalkable(int cellType, float localX, float localY) {

    // Область комнаты
    const bool ROOM_RECT = localX >= ROOM_MARGIN_LEFT && localX <= ROOM_MARGIN_RIGHT &&
                           localY >= ROOM_MARGIN_TOP && localY <= ROOM_MARGIN_BOTTOM;

    // Проверка нахождения в области
    switch (cellType) {
        case 101: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT || localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 102: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT) || (localX >= CELL_MARGIN_LEFT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 103: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT) || (localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 104: return ROOM_RECT || (localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP);
        case 105: return ROOM_RECT || (localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY <= CELL_MARGIN_BOTTOM);
        case 106: return ROOM_RECT || (localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 107: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT);
        case 108: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY <= CELL_MARGIN_BOTTOM);
        case 109: return ROOM_RECT || (localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY <= CELL_MARGIN_BOTTOM);
        case 110: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP);
        case 111: return ROOM_RECT || (localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP);
        case 112: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP);
        case 113: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 114: return ROOM_RECT || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY <= CELL_MARGIN_BOTTOM);
        case 115: return ROOM_RECT || (localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
    }
    return false;
}



bool MapManager::isCorridorWalkable(int cellType, float localX, float localY) {

    // Проверка нахождения в области
    switch (cellType) {
        case 201: return (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT || localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 202: return (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT) || (localX >= CELL_MARGIN_LEFT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 203: return (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT) || (localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 204: return (localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP);
        case 205: return (localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY <= CELL_MARGIN_BOTTOM);
        case 206: return (localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM);
        case 207: return (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT);
        case 208: return (localX >= CELL_MARGIN_LEFT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY <= CELL_MARGIN_BOTTOM);
        case 209: return (localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY <= CELL_MARGIN_BOTTOM);
        case 210: return (localX >= CELL_MARGIN_LEFT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP);
        case 211: return (localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP && localY <= CELL_MARGIN_BOTTOM) || (localX >= CELL_MARGIN_LEFT && localX <= CELL_MARGIN_RIGHT && localY >= CELL_MARGIN_TOP);
    }
    return false;
}



void MapManager::precomputeWalkabilityMasks() {

    // Использую uint64_t для 64-битной маски
    walkabilityMasks.resize(MAP_HEIGHT, std::vector<uint64_t>(MAP_WIDTH, 0));

    // Делю ячейку на 8x8
    int numDivisions = 8;
    int subCellSize = CELL_SIZE / numDivisions;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            int cellType = map.getGrid()[y][x];
            uint64_t mask = 0;

            for (int localY = 0; localY < numDivisions; ++localY) {
                for (int localX = 0; localX < numDivisions; ++localX) {
                    int bitIndex = localY * numDivisions + localX;
                    float checkX = localX * subCellSize + 0.5f * subCellSize;
                    float checkY = localY * subCellSize + 0.5f * subCellSize;

                    if (isCellWalkable(cellType, checkX, checkY)) {
                        mask |= (uint64_t(1) << bitIndex); // Устанавливаем соответствующий бит
                    }
                }
            }
            walkabilityMasks[y][x] = mask;
        }
    }
}


bool MapManager::isCellWalkable(int cellType, float localX, float localY) {

    // Если это комната
    if (cellType / 100 == 1) {
        return isRoomWalkable(cellType, localX, localY);
    }

    // Если это коридор
    if (cellType / 100 == 2) {
        return isCorridorWalkable(cellType, localX, localY);
    }

    // Если это комната появления или с боссом
    if (cellType / 100 == 5 || cellType / 100 == 6) {
     return true;
    }

    return false;
}
