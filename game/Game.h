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
    void processMenu(const sf::Event& event, sf::RenderWindow& window);
    void processSelectionButton(const sf::Event& event);
    void updateDeltaTime();
    void updateCamera(sf::RenderWindow& window);
    static bool processControllerConnect();

    GameState state;
    sf::Clock clock;
    float deltaTime;
    float globalTime;
    sf::View view;

    std::unique_ptr<Player> player;
    std::unique_ptr<Enemy> enemy;
};
