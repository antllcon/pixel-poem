// Game.h

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Player;
class Enemy;

class Game
{
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
    void initEntitiesPlay();
    void updateDeltaTime();
    void updateCamera(sf::RenderWindow& window);

    GameState state;
    sf::Clock clock;
    float deltaTime;
    sf::View view;

    std::unique_ptr<Player> player;
    std::unique_ptr<Enemy> enemy;
};
