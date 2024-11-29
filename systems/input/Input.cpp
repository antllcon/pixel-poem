#include "Input.h"

#include <iostream>
#include "../../core/config.h"

Input::Input() {
    resetStates();
}

bool Input::processControllerConnect() {
    sf::Joystick::update();
    if (sf::Joystick::isConnected(0)) return true;
    return false;
}

void Input::checkRightStick(unsigned int joystickId) {
    if (!sf::Joystick::isConnected(joystickId)) {
        return;
    }

    float rightX = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::U);
    float rightY = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::R);

    // std::cout << "Right Stick - X: " << rightX << ", Y: " << rightY << std::endl;
}

bool Input::isPressed(const std::string& action) const {
    auto it = buttonStates.find(action);
    if (it != buttonStates.end()) {
        return it->second.currentState;
    }
    return false;
}

void Input::processInput() {
    if (processControllerConnect()) {
        checkHeldGamepadButtons();  // Проверка кнопок геймпада
        checkHeldGamepadAxes();     // Проверка стиков геймпада
    } else {
        checkHeldKeys();            // Проверка клавиш клавиатуры
    }
}

void Input::resetStates() {
    buttonStates["moveUp"] = {false};
    buttonStates["moveDown"] = {false};
    buttonStates["moveLeft"] = {false};
    buttonStates["moveRight"] = {false};
    buttonStates["jump"] = {false};
    buttonStates["attack"] = {false};
    buttonStates["pause"] = {false};
    buttonStates["start"] = {false};
    buttonStates["select"] = {false};
    buttonStates["leftStickPress"] = {false};
    buttonStates["rightStickPress"] = {false};
}

void Input::updateButtonState(const std::string& action, bool isPressed) {
    buttonStates[action].currentState = isPressed;
}

void Input::checkHeldKeys() {
    // сделать мапу и проходить в цикле
    updateButtonState("moveLeft", sf::Keyboard::isKeyPressed(sf::Keyboard::A));
    updateButtonState("moveRight", sf::Keyboard::isKeyPressed(sf::Keyboard::D));
    updateButtonState("moveUp", sf::Keyboard::isKeyPressed(sf::Keyboard::W));
    updateButtonState("moveDown", sf::Keyboard::isKeyPressed(sf::Keyboard::S));
    updateButtonState("shoot", sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
    updateButtonState("approve", sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
    updateButtonState("exit", sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
    updateButtonState("lookUp", sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    updateButtonState("lookDown", sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    updateButtonState("lookLeft", sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    updateButtonState("lookRight", sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
}

void Input::checkHeldGamepadButtons() {
    unsigned int joystickId = 0;
    updateButtonState("approve", sf::Joystick::isButtonPressed(joystickId, 0)); // Cross
    updateButtonState("", sf::Joystick::isButtonPressed(joystickId, 1)); // Circle
    updateButtonState("", sf::Joystick::isButtonPressed(joystickId, 2)); // Triangle
    updateButtonState("", sf::Joystick::isButtonPressed(joystickId, 3)); // Rectangle
    updateButtonState("", sf::Joystick::isButtonPressed(joystickId, 4)); // L1
    updateButtonState("", sf::Joystick::isButtonPressed(joystickId, 5)); // R1
    updateButtonState("", sf::Joystick::isButtonPressed(joystickId, 6)); // L2
    updateButtonState("shoot", sf::Joystick::isButtonPressed(joystickId, 7)); // R2
    updateButtonState("exit", sf::Joystick::isButtonPressed(joystickId, 10)); // Exit
}

void Input::checkHeldGamepadAxes() {// декомпозировать
    unsigned int joystickId = 0;

    // Левый стик (движение)
    float leftX = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
    float leftY = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y);

    // Вверх/вниз (левый стик)
    if (leftY < -DEAD_ZONE) {
        updateButtonState("moveUp", true);
    } else if (leftY > DEAD_ZONE) {
        updateButtonState("moveDown", true);
    } else {
        updateButtonState("moveUp", false);
        updateButtonState("moveDown", false);
    }

    // Влево/вправо (левый стик)
    if (leftX < -DEAD_ZONE) {
        updateButtonState("moveLeft", true);
    } else if (leftX > DEAD_ZONE) {
        updateButtonState("moveRight", true);
    } else {
        updateButtonState("moveLeft", false);
        updateButtonState("moveRight", false);
    }

    // Правый стик (взгляд)
    float rightX = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::U); // Горизонтальная ось
    float rightY = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::V); // Вертикальная ось

    // Вывод значений осей для отладки
    // std::cout << "Right Stick - X: " << rightX << ", Y: " << rightY << std::endl;

    // Вправо/влево/вверх/вниз (правый стик, по 90 градусов)
    if (std::abs(rightX) > std::abs(rightY)) {
        // Горизонтальное направление доминирует
        if (rightX > DEAD_ZONE) {
            updateButtonState("lookRight", true);
            updateButtonState("lookLeft", false);
            updateButtonState("lookUp", false);
            updateButtonState("lookDown", false);
        } else if (rightX < -DEAD_ZONE) {
            updateButtonState("lookLeft", true);
            updateButtonState("lookRight", false);
            updateButtonState("lookUp", false);
            updateButtonState("lookDown", false);
        }
    } else {
        // Вертикальное направление доминирует
        if (rightY > DEAD_ZONE) {
            updateButtonState("lookDown", true);
            updateButtonState("lookUp", false);// слишком нагруженно выглядит
            updateButtonState("lookLeft", false);
            updateButtonState("lookRight", false);
        } else if (rightY < -DEAD_ZONE) {
            updateButtonState("lookUp", true);
            updateButtonState("lookDown", false);
            updateButtonState("lookLeft", false);
            updateButtonState("lookRight", false);
        }
    }
}
