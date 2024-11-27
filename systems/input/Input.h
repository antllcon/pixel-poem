#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Window.hpp>
#include <unordered_map>
#include <string>

class Input {
public:
    Input();

    // Проверка подключения контроллера
    static bool processControllerConnect();

    static void checkRightStick(unsigned int joystickId);

    // Обработка ввода
    void processInput();

    // Проверка состояния кнопки
    bool isPressed(const std::string& action) const;

    // Сброс всех состояний
    void resetStates();


private:
    struct ButtonState {
        bool currentState = false;
    };

    // Состояния кнопок
    std::unordered_map<std::string, ButtonState> buttonStates;

    // Обработка нажатий и действий
    void checkHeldKeys();
    void checkHeldGamepadButtons();
    void checkHeldGamepadAxes();

    // Обновление состояния нажатия
    void updateButtonState(const std::string& action, bool isPressed);
};

#endif // INPUT_HANDLER_H
