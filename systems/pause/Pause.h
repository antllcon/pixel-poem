#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../input/Input.h"

class Pause {
public:
    Pause();

    void processPause(const Input& inputHandler);
    void renderPause(const Input& inputHandler, sf::RenderWindow &window);
    int getSelectedOption() const;

private:
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text resumeText;
    sf::Text menuText;
    sf::Texture textureController;
    sf::Sprite spriteController;
    sf::VertexArray gradient;
    int selectedOption;

    void initTextPause();
    void initControllerStatus();
};
