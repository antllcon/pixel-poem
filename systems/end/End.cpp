#include "End.h"


#include "../../core/config.h"

End::End(int money): money(money) {
    initTextEnd();
    selectedOption = 0;

}

void End::initTextEnd() {
    font.loadFromFile(SRC_FONT_HARRY);

    gradient.setPrimitiveType(sf::Quads);
    gradient.resize(4);

    gradient[0].position = sf::Vector2f(0, 0);
    gradient[0].color = COLOR_BLACK;

    gradient[1].position = sf::Vector2f(SCREEN_WIDTH / 2.f, 0);
    gradient[1].color = COLOR_TRANSPARENT;

    gradient[2].position = sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT);
    gradient[2].color = COLOR_TRANSPARENT;

    gradient[3].position = sf::Vector2f(0, SCREEN_HEIGHT);
    gradient[3].color = COLOR_BLACK;

    titleText.setFont(font);
    titleText.setString("Pixel Poem");
    titleText.setCharacterSize(64);
    titleText.setFillColor(COLOR_RED);
    titleText.setPosition(GAP_TEXT_PAUSE_X,
                          SCREEN_HEIGHT / 2.0f - 150);
    titleText.setOutlineThickness(UI_OUTLINE);
    titleText.setOutlineColor(COLOR_BLACK);

    subtitleText.setFont(font);
    subtitleText.setString("End of game!");
    subtitleText.setCharacterSize(48);
    subtitleText.setFillColor(COLOR_RED);
    subtitleText.setPosition(GAP_TEXT_PAUSE_X,
                             SCREEN_HEIGHT / 2.0f - 100);
    subtitleText.setOutlineThickness(UI_OUTLINE);
    subtitleText.setOutlineColor(COLOR_BLACK);

    resultsText.setFont(font);
    resultsText.setString("Your money - " + std::to_string(money));
    resultsText.setCharacterSize(30);
    resultsText.setFillColor(COLOR_GOLD);
    resultsText.setPosition(GAP_TEXT_PAUSE_X, SCREEN_HEIGHT / 2.0f);
    resultsText.setOutlineThickness(UI_OUTLINE);
    resultsText.setOutlineColor(COLOR_BLACK);

    menuText.setFont(font);
    menuText.setString("Exit to menu");
    menuText.setCharacterSize(30);
    menuText.setFillColor(COLOR_GRAY);
    menuText.setPosition(GAP_TEXT_PAUSE_X, SCREEN_HEIGHT / 2.0f + 30);
    menuText.setOutlineThickness(UI_OUTLINE);
    menuText.setOutlineColor(COLOR_BLACK);


    texture.loadFromFile(SRC_SKULL);

    sprite.setTexture(texture);
    sprite.setPosition(GAP_TEXT_PAUSE_X,
                                 SCREEN_HEIGHT / 2 + 100);
    sprite.setScale(SCALE_FACTOR_DOWN);

}

void End::processEnd(const Input& inputHandler) {
    if (inputHandler.isPressed("moveUp")) {
        selectedOption = 0;
        resultsText.setFillColor(COLOR_GOLD);
        menuText.setFillColor(COLOR_GRAY);
    }
    if (inputHandler.isPressed("moveDown")) {
        selectedOption = 1;
        resultsText.setFillColor(COLOR_GOLD);
        menuText.setFillColor(COLOR_PURPLE);
    }
}

void End::renderEnd(sf::RenderWindow& window) {
    window.draw(gradient);
    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(resultsText);
    window.draw(menuText);
    window.draw(sprite);

}

int End::getSelectedOption() const {
    return selectedOption;
}
