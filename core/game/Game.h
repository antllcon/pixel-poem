#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "../../entities/entity/EntityManager.h"
#include "../../systems/camera/CameraManager.h"
#include "../../systems/collision/CollisionManager.h"
#include "../../systems/map/MapManager.h"
#include "../../systems/input/Input.h"
#include "../../systems/menu/Menu.h"
#include "../../systems/ui/UI.h"
#include "GameStateManager.h"
#include "../../systems/pause/Pause.h"
#include "../../systems/end/End.h"

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
    EntityManager entityManager;
    CollisionManager collisionManager;
    CameraManager cameraManager;
    MapManager mapManager;
    Input inputHandler;
    Menu menu;
    Pause pause;
    End* end;
    UI* ui;

    sf::Clock clock;
    sf::View view;
    float globalTime;
    float deltaTime;
    float lastStateChangeTime;

    void handleStartEvents(sf::RenderWindow& window);
    void handlePlayEvents();
    void handlePauseEvents();
    void handleEndEvents();
    void initEntitiesPlay();
    void updateDeltaTime();
    void updateCamera(sf::RenderWindow& window);

    bool canChangeState();
    void changeState(GameStateManager::GameState newState);

};
