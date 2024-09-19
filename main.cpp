#include <iostream>
#include <SFML/Graphics.hpp>
#include "character/Character.hpp"

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
        "Pixel Poem");

    Character hero(400.0f, 300.0f, 0.2f, 20, 60, 1);

    while (window.isOpen()) {
        sf::Event event = sf::Event();

        float moveX = 0.0f;
        float moveY = 0.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            moveX -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            moveX += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            moveY -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            moveY += 1.0f;
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        hero.move(moveX, moveY);

        // Очищаем экран и отрисовываем персонажа
        window.clear();
        hero.draw(window);
        window.display();

        // drawCircleCenter(window, 64.0f);
    }

    std::cout << "@antllcon production" << std::endl;
    return 0;
}
