#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "../../entities/entity/EntitiyManager.h"
#include "../../systems/camera/CameraManager.h"
#include "../../systems/collision/CollisionManager.h"
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
    EntityManager entityManager;
    CollisionManager collisionManager;
    CameraManager cameraManager;
    Input inputHandler;
    Menu menu;
    Map map;
    UI* ui;

    sf::Clock clock;
    sf::View view;
    float globalTime;
    float deltaTime;

    void handleStartEvents(sf::RenderWindow& window);
    void handlePlayEvents();
    void handlePauseEvents();
    void handleEndEvents();
    void initEntitiesPlay();
    void updateDeltaTime();
    void updateCamera(sf::RenderWindow& window);
};
