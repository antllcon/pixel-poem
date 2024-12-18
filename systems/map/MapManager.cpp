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
    std::cout << " Расчет проходимых областей " << std::endl;
    precomputeWalkabilityMasks();
    std::cout << " Раскраска карты " << std::endl;
    loadTextures();
    map.printMap();
}



void MapManager::loadTextures() {
    for (int id = 101; id <= 115; ++id) {
        sf::Texture texture;
        if (texture.loadFromFile(SRC_ROOM + std::to_string(id) + PNG)) {
            textures[id] = texture;
        }
    }
    for (int id = 201; id <= 211; ++id) {
        sf::Texture texture;
        if (texture.loadFromFile(SRC_TRANSITION + std::to_string(id) + PNG)) {
            textures[id] = texture;
        }
    }
}


void MapManager::render(sf::RenderWindow& window) {
    const auto& grid = map.getGrid();
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 0) {
                continue;
            }

            sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            sprite.setScale(SCALE_FACTOR);

            auto it = textures.find(grid[y][x]);
            if (it != textures.end()) {
                sprite.setTexture(it->second);
                window.draw(sprite);
            }
        }
    }
}






std::vector<std::vector<int>>& MapManager::getMap() { return map.getGrid(); }






sf::Vector2f MapManager::getPlayerRoomPosition() {
    return sf::Vector2f(map.getStartRoom());
}


sf::Vector2f MapManager::getBossRoomPosition() {
    return sf::Vector2f(map.getEndRoom());
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

    int numDivisions = 32;
    int subCellSize = CELL_SIZE / numDivisions;

    int localX = (x % CELL_SIZE) / subCellSize;
    int localY = (y % CELL_SIZE) / subCellSize;

    int globalBitIndex = localY * numDivisions + localX;
    int maskIndex = globalBitIndex / 64;
    int localBitIndex = globalBitIndex % 64;

    return walkabilityMasks[cellY][cellX][maskIndex] & (uint64_t(1) << localBitIndex);
}



bool MapManager::isRoomWalkable(int cellType, float localX, float localY) {

    const bool ROOM_RECT = localX >= ROOM_MARGIN_LEFT && localX <= ROOM_MARGIN_RIGHT &&
                           localY >= ROOM_MARGIN_TOP && localY <= ROOM_MARGIN_BOTTOM;

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
    // Делю ячейку
    int numDivisions = 32;
    int subCellSize = CELL_SIZE / numDivisions;
    int numMasks = (numDivisions * numDivisions) / 64;

    // Ресайзим маску
    walkabilityMasks.resize(MAP_HEIGHT, std::vector<std::vector<uint64_t>>(MAP_WIDTH, std::vector<uint64_t>(numMasks, 0)));

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            int cellType = map.getGrid()[y][x];

            for (int localY = 0; localY < numDivisions; ++localY) {
                for (int localX = 0; localX < numDivisions; ++localX) {
                    // Осмыслить
                    int globalBitIndex = localY * numDivisions + localX;
                    int maskIndex = globalBitIndex / 64;
                    int localBitIndex = globalBitIndex % 64;

                    // Коэффициенты осмыслить
                    float checkX = localX * subCellSize + 0.5f * subCellSize;
                    float checkY = localY * subCellSize + 0.5f * subCellSize;

                    if (isCellWalkable(cellType, checkX, checkY)) {
                        walkabilityMasks[y][x][maskIndex] |= (uint64_t(1) << localBitIndex);
                    }
                }
            }
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

    return false;
}
