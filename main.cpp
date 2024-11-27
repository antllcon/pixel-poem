#include "core/config.h"
#include "core/game/Game.h"

int main() {
    // Инициализация экрана
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Pixel Poem");

    // Инициализация игры
    Game pixelPoem;
    pixelPoem.setState(Game::GameState::Start);

    // Цикл игры
    while (window.isOpen()) {
        pixelPoem.processEvents(window);
        pixelPoem.update(window);
        pixelPoem.render(window);
    }
    return 0;
}
