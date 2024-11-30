#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../input/Input.h"

class Menu {
   public:
    Menu();

    void processMenu(const Input& inputHandler);
    void renderMenu(const Input& inputHandler, sf::RenderWindow &window);
    int getSelectedOption() const;

   private:
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text winEndText;
    sf::Text lossEndText;
    sf::Text startText;
    sf::Text exitText;
    sf::Text pauseText;
    sf::Texture textureController;
    sf::Sprite spriteController;
    int selectedOption;

    void initTextMenu();
    void initControllerStatus();
};
