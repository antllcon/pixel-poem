#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "../../systems/input/Input.h"
#include "../../systems/map/Map.h"
#include "../../systems/menu/Menu.h"
#include "../../systems/ui/UI.h"
#include "GameStateManager.h"

class Bullet;
class Player;
class Enemy;

class Game {
   public:
    Game();
    ~Game();

    void processEvents(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    GameStateManager& getStateManager();

   private:
    GameStateManager gameStateManager;
    sf::Clock clock;
    sf::View view;
    Menu menu;
    Map map;
    Input inputHandler;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Bullet> bullets;
    UI* ui;

    float globalTime;
    float deltaTime;

    void handleStartEvents(sf::RenderWindow& window);
    void handlePlayEvents();
    void handlePauseEvents();
    void handleEndEvents();
    void initEntitiesPlay();
    void spawnPlayer();
    void spawnEnemies(int numEnemies);
    void updateEnemy();
    void updateBullets();
    void updateDeltaTime();
    void updateCamera(sf::RenderWindow& window);
    void checkCollisions();
    void checkBulletEnemyCollisions();
    void checkBulletPlayerCollisions();
    void checkPlayerEnemyCollisions();
};
