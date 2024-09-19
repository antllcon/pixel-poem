#include <iostream>
#include <SFML/Graphics.hpp>

void drawCircleCenter(sf::RenderWindow& window, float radius) {

    sf::Vector2u windowSize = window.getSize(); // что такое

    float x = static_cast<float>(windowSize.x) / 2 - radius;
    float y = static_cast<float>(windowSize.y) / 2 - radius;

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Green); // задаем цвет

    circle.setPosition(x, y);

    window.clear();
    window.draw(circle);
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600),
        "Game title");

    while (window.isOpen()) {
        sf::Event event = sf::Event();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        drawCircleCenter(window, 64.0f);
    }

    std::cout << "test version - 1" << std::endl;
    return 0;
}
