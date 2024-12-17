#include "Pause.h"


#include "../../core/config.h"

Pause::Pause() {
    initTextPause();
    initControllerStatus();
    selectedOption = 0;
    resumeText.setFillColor(COLOR_GREEN);
}

void Pause::initTextPause() {
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
    titleText.setFillColor(COLOR_PURPLE);
    titleText.setPosition(GAP_TEXT_PAUSE_X,
                          SCREEN_HEIGHT / 2.0f - 150);
    titleText.setOutlineThickness(UI_OUTLINE);
    titleText.setOutlineColor(COLOR_BLACK);

    subtitleText.setFont(font);
    subtitleText.setString("Pause");
    subtitleText.setCharacterSize(48);
    subtitleText.setFillColor(COLOR_LIGHT_YELLOW);
    subtitleText.setPosition(GAP_TEXT_PAUSE_X,
                             SCREEN_HEIGHT / 2.0f - 100);
    subtitleText.setOutlineThickness(UI_OUTLINE);
    subtitleText.setOutlineColor(COLOR_BLACK);

    resumeText.setFont(font);
    resumeText.setString("Resume game");
    resumeText.setCharacterSize(30);
    resumeText.setFillColor(COLOR_GRAY);
    resumeText.setPosition(GAP_TEXT_PAUSE_X, SCREEN_HEIGHT / 2.0f);
    resumeText.setOutlineThickness(UI_OUTLINE);
    resumeText.setOutlineColor(COLOR_BLACK);

    menuText.setFont(font);
    menuText.setString("Exit to menu");
    menuText.setCharacterSize(30);
    menuText.setFillColor(COLOR_GRAY);
    menuText.setPosition(GAP_TEXT_PAUSE_X, SCREEN_HEIGHT / 2.0f + 30);
    menuText.setOutlineThickness(UI_OUTLINE);
    menuText.setOutlineColor(COLOR_BLACK);
}

void Pause::initControllerStatus() {
    textureController.loadFromFile(SRC_CONTROLLER);

    spriteController.setTexture(textureController);
    spriteController.setPosition(GAP_TEXT_PAUSE_X,
                                 SCREEN_HEIGHT / 2 + 100);
    spriteController.setScale(0.05f, 0.05f);
}

void Pause::processPause(const Input& inputHandler) {
    if (inputHandler.isPressed("moveUp")) {
        selectedOption = 0;
        resumeText.setFillColor(COLOR_GREEN);
        menuText.setFillColor(COLOR_GRAY);
    }
    if (inputHandler.isPressed("moveDown")) {
        selectedOption = 1;
        resumeText.setFillColor(COLOR_GRAY);
        menuText.setFillColor(COLOR_GREEN);
    }
}

void Pause::renderPause(const Input& inputHandler, sf::RenderWindow& window) {
    window.draw(gradient);
    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(resumeText);
    window.draw(menuText);
    if (inputHandler.processControllerConnect()) {
        window.draw(spriteController);
    }
}

int Pause::getSelectedOption() const {
    return selectedOption;
}
