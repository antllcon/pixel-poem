#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../input/Input.h"

class End {
public:
    End(int money);

    void processEnd(const Input& inputHandler);
    void renderEnd(sf::RenderWindow &window);
    int getSelectedOption() const;

private:
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text resultsText;
    sf::Text menuText;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::VertexArray gradient;
    int selectedOption;
    int money;

    void initTextEnd();
};
