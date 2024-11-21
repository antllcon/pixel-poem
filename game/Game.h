// Game.h

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../input/input.h"

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
    // Обработчик ввода
    void testInputHandler();
    Input inputHandler;

    // меню
    sf::Texture textureController;
    sf::Sprite spriteController;
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text startText;
    sf::Text exitText;
    int selectedOption; // 0 - Start, 1 - Exit

    void initMenu();
    void initEntitiesPlay();
    void initControllerStatus();
    void processMenu(sf::RenderWindow& window);
    void processSelectionButton();
    void updateDeltaTime();
    void updateCamera(sf::RenderWindow& window);

    GameState state;
    sf::Clock clock;
    float deltaTime;
    float globalTime;
    sf::View view;

    std::unique_ptr<Player> player;
    std::unique_ptr<Enemy> enemy;
};
