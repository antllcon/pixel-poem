
#ifndef CONFIG_H
#define CONFIG_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
// === Цветовые настройки ===
const sf::Color COLOR_LIGHT_YELLOW = sf::Color(255, 255, 200);
const sf::Color COLOR_DARK_PURPLE = sf::Color(64, 28, 47);
const sf::Color COLOR_GREEN = sf::Color(102, 153, 102);
const sf::Color COLOR_PURPLE = sf::Color(204, 0, 102);
const sf::Color COLOR_BRAUN = sf::Color(100, 73, 73);
const sf::Color COLOR_GRAY = sf::Color(69, 69, 69);
const sf::Color COLOR_DARK = sf::Color(51, 51, 51);
const sf::Color COLOR_RED = sf::Color(153, 0, 0);
const sf::Color COLOR_GOLD = sf::Color(239, 191, 4);
const sf::Color COLOR_BLACK = sf::Color(33, 33, 33);
const sf::Color COLOR_WHITE = sf::Color(255, 255, 255);
const sf::Color COLOR_BLUE = sf::Color(100, 0, 255);
const sf::Color COLOR_TRANSPARENT = sf::Color(0, 0, 0, 0);

// === Основные настройки игры ===
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;
constexpr int ROOM_COUNT = 7;
constexpr int MAP_WIDTH = 9;
constexpr int MAP_HEIGHT = 9;
constexpr int CELL_SIZE = 256;
constexpr float CAMERA_DELTA_WIDTH = SCREEN_WIDTH / 6.f;
constexpr float CAMERA_DELTA_HEIGHT = SCREEN_HEIGHT / 6.f;
constexpr int DEAD_ZONE = 5.0f;
constexpr float COLLISION_BOUNCE_FACTOR = 0.5f;
constexpr int GAP_TEXT_PAUSE_X = 100;
constexpr float STATE_CHANGE_COOLDOWN = 0.5f;
constexpr float INIT_ZERO_TIME = 0.f;

// === Настройки игрока ===
const sf::Vector2f PLAYER_VIEW(1.0f, 0.0f);
const sf::Vector2f PLAYER_MOVE_DIRECTION = sf::Vector2f(0.f, 0.f);
const sf::Color PLAYER_COLOR = sf::Color(78, 162, 122);
constexpr float PLAYER_SPEED = 100.f;
constexpr float PLAYER_REGENERATION_COOLDOWN = 3.f;
constexpr int PLAYER_REGENERATION_ARMOR = 1;
constexpr int PLAYER_SIZE = 24;
constexpr int PLAYER_HEALTH = 10;
constexpr int PLAYER_ARMOR = 20;
constexpr int PLAYER_MONEY = 0;
constexpr float MAP_PLAYER_SPAWN_X = 128.f;
constexpr float MAP_PLAYER_SPAWN_Y = 128.f;

// === Настройки врагов (ботов) ===
const sf::Color BOT_COLOR = sf::Color(150, 50, 50);
constexpr int BOT_SIZE = 24;
constexpr int BOT_HEALTH = 5;
constexpr float BOT_SPEED = 100.f;
constexpr float BOT_DIRECTION_CHANGE_INTERVAL = 2.f;
constexpr float BOT_DIRECTION_CHANGE_TIME = 0.f;
constexpr float BOT_VIEW_SIZE = 128.f;
constexpr int NUM_ENEMIES = 100;
const sf::FloatRect BOT_VIEW_AREA(
    -BOT_VIEW_SIZE, -BOT_VIEW_SIZE,
    BOT_VIEW_SIZE * 2 + BOT_SIZE,
    BOT_VIEW_SIZE * 2 + BOT_SIZE
);
constexpr float MAP_BOT_SPAWN_X = 120.f;
constexpr float MAP_BOT_SPAWN_Y = 20.f;

// === Настройки оружия и пуль ===
constexpr float WEAPON_DESERT_EAGLE = 0.25f;
constexpr float WEAPON_COOLDOWN = 0.25f;
const sf::Color BULLET_COLOR = COLOR_GREEN;
constexpr int BULLET_SIZE = 10;
constexpr int BULLET_SPEED = 500.f;
constexpr int BULLET_DAMAGE = 10;

// === Настройки интерфейса (UI) ===
constexpr int UI_TEXT = 14;
constexpr float UI_OUTLINE = 4.f;

const sf::Vector2f BACKGROUND_PLATFORM_SIZE = sf::Vector2f(180.f, 85.f);
const sf::Vector2f BACKGROUND_PLATFORM_POS = sf::Vector2f(SCREEN_WIDTH - 195.f, SCREEN_HEIGHT - 100.f);

const sf::Vector2f BAR_SIZE = sf::Vector2f(160.f, 10.f);
const sf::Vector2f HEALTH_BACKGROUND_POS = sf::Vector2f(SCREEN_WIDTH - 185.f, SCREEN_HEIGHT - 75.f);
const sf::Vector2f HEALTH_BAR_POS = sf::Vector2f(SCREEN_WIDTH - 185.f, SCREEN_HEIGHT - 75.f);
const sf::Vector2f HEALTH_TEXT_POS = sf::Vector2f(SCREEN_WIDTH - 115.f, SCREEN_HEIGHT - 98.f);

const sf::Vector2f ARMOR_BACKGROUND_POS = sf::Vector2f(SCREEN_WIDTH - 185.f, SCREEN_HEIGHT - 35.f);
const sf::Vector2f ARMOR_BAR_POS = sf::Vector2f(SCREEN_WIDTH - 185.f, SCREEN_HEIGHT - 35.f);
const sf::Vector2f ARMOR_TEXT_POS = sf::Vector2f(SCREEN_WIDTH - 105.f, SCREEN_HEIGHT - 58.f);

const sf::Vector2f MONEY_SPRITE_POS = sf::Vector2f(SCREEN_WIDTH - 45, 10);
const sf::Vector2f MONEY_TEXT_POS = sf::Vector2f(SCREEN_WIDTH - 55, 18);

// === Масштабирование текстур ===
const sf::Vector2f SCALE_FACTOR_LEFT = {2.2f, 2.2f};
const sf::Vector2f SCALE_FACTOR_RIGHT = {-2.2f, 2.2f};
const sf::Vector2f SCALE_FACTOR_UP = {2.2f, -2.2f};
const sf::Vector2f SCALE_FACTOR_DOWN = {2.2f, 2.2f};

// === Анимации ===
constexpr float ANIMATION_SPEED = 0.2f;

// === Ресурсы ===
const std::string SRC_FONT_HARRY = "/projects/CLionProjects/pixel_poem/resources/fonts/Harry.ttf";
const std::string SRC_FONT_MONOCRAFT = "/projects/CLionProjects/pixel_poem/resources/fonts/Monocraft.otf";
const std::string SRC_CONTROLLER = "/projects/CLionProjects/pixel_poem/resources/textures/controller.png";
const std::string SRC_UI_COIN = "/projects/CLionProjects/pixel_poem/resources/textures/coin.png";
const std::string SRC_SKULL = "/projects/CLionProjects/pixel_poem/resources/textures/skull.png";
const std::string SRC_SKELETON = "/projects/CLionProjects/pixel_poem/resources/sprites/skeleton/skeleton_";
const std::string SRC_KNIGHT = "/projects/CLionProjects/pixel_poem/resources/sprites/knight/knight_";
const std::string SRC_ARROW = "/projects/CLionProjects/pixel_poem/resources/sprites/arrow/arrow_";
const std::string PNG = ".png";

#endif
