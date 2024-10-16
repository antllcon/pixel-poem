// config.h

#ifndef CONFIG_H
#define CONFIG_H

// Размеры окна игры
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

// Координаты появления игрока на карте (в px)
constexpr float MAP_PLAYER_SPAWN_X = 20.f;
constexpr float MAP_PLAYER_SPAWN_Y = 20.f;

// Координаты появления врага на карте (в px)
constexpr float MAP_BOT_SPAWN_X = 120.f;
constexpr float MAP_BOT_SPAWN_Y = 20.f;


// Характеристики игрока
constexpr int PLAYER_SIZE = 24;
constexpr int PLAYER_HEALTH = 100;
constexpr float PLAYER_SPEED = 250.f;
const sf::Color PLAYER_COLOR = sf::Color(78, 162, 122);

constexpr int BOT_SIZE = 24;
constexpr int BOT_HEALTH = 25;
const sf::Color BOT_COLOR = sf::Color(150, 50, 50);

#endif
