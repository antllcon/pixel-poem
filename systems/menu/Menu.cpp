#include "Menu.h"

#include "../../core/config.h"

Menu::Menu() {
    initTextMenu();
    initControllerStatus();
    selectedOption = 0;
    startText.setFillColor(COLOR_GREEN);
}

void Menu::initTextMenu() {
    font.loadFromFile(SRC_FONT);

    titleText.setFont(font);
    titleText.setString("Pixel Poem");
    titleText.setCharacterSize(64);
    titleText.setFillColor(COLOR_PURPLE);
    titleText.setPosition(SCREEN_WIDTH / 2.0f - 160,
                          SCREEN_HEIGHT / 2.0f - 150);

    subtitleText.setFont(font);
    subtitleText.setString("Dungeon");
    subtitleText.setCharacterSize(48);
    subtitleText.setFillColor(COLOR_PURPLE);
    subtitleText.setPosition(SCREEN_WIDTH / 2.0f - 100,
                             SCREEN_HEIGHT / 2.0f - 100);

    startText.setFont(font);
    startText.setString("Play");
    startText.setCharacterSize(30);
    startText.setFillColor(COLOR_GRAY);
    startText.setPosition(SCREEN_WIDTH / 2.0f - 30, SCREEN_HEIGHT / 2.0f);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(COLOR_GRAY);
    exitText.setPosition(SCREEN_WIDTH / 2.0f - 30, SCREEN_HEIGHT / 2.0f + 30);

    winEndText.setFont(font);
    winEndText.setString("You are win!");
    winEndText.setCharacterSize(64);
    winEndText.setFillColor(COLOR_PURPLE);
    winEndText.setPosition(SCREEN_WIDTH / 2.0f - 160,
                           SCREEN_HEIGHT / 2.0f - 150);

    lossEndText.setFont(font);
    lossEndText.setString("You are loss!");
    lossEndText.setCharacterSize(64);
    lossEndText.setFillColor(COLOR_RED);
    lossEndText.setPosition(SCREEN_WIDTH / 2.0f - 160,
                            SCREEN_HEIGHT / 2.0f - 150);
}

void Menu::initControllerStatus() {
    textureController.loadFromFile(SRC_CONTROLLER);

    spriteController.setTexture(textureController);
    spriteController.setPosition(SCREEN_WIDTH / 2 - 30,
                                 SCREEN_HEIGHT / 2 + 100);
    spriteController.setScale(0.05f, 0.05f);
}

void Menu::processMenu(const Input& inputHandler) {
    if (inputHandler.isPressed("moveUp")) {
        selectedOption = 0;
        startText.setFillColor(COLOR_GREEN);
        exitText.setFillColor(COLOR_GRAY);
    }
    if (inputHandler.isPressed("moveDown")) {
        selectedOption = 1;
        exitText.setFillColor(COLOR_GREEN);
        startText.setFillColor(COLOR_GRAY);
    }
}

void Menu::renderMenu(const Input& inputHandler, sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(startText);
    window.draw(exitText);
    if (inputHandler.processControllerConnect()) {
        window.draw(spriteController);
    }
}

int Menu::getSelectedOption() const {
    return selectedOption;
}
