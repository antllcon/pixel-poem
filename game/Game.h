#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../input/Input.h"
#include "../menu/Menu.h"

class Player;
class Enemy;

class Game {
   public:
    enum class GameState { Start, Play, Pause, End };

    Game();
    ~Game();

    void processEvents(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void setState(GameState newState);
    GameState getState() const;

   private:
    GameState state;
    sf::Clock clock;
    sf::View view;
    Menu menu;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    Input inputHandler;

    float globalTime;
    float deltaTime;

    void handleStartEvents(sf::RenderWindow& window);
    void handlePlayEvents();
    void handlePauseEvents();
    void handleEndEvents();
    void initEntitiesPlay();
    void spawnPlayer();
    void spawnEnemies(int numEnemies);
    void updateDeltaTime();
    void updateCamera(sf::RenderWindow& window);
};
