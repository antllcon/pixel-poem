#include <iostream>
#include <SFML/Graphics.hpp>

// void drawRectangle(sf::RenderWindow &window, float x, float y, float width, float height, float color); {
//     sf::RectangleShape rectangle(sf::Vector2f(width, height));
//     rectangle.setPosition(x, y);
//     rectangle.setFillColor(sf::Color::Black);
// }

//
// void drawCircleCenter(sf::RenderWindow& window, float x, float y, float radius) {
//
//     sf::Vector2u windowSize = window.getSize();
//
//     float x = static_cast<float>(windowSize.x) / 2 - radius;
//     float y = static_cast<float>(windowSize.y) / 2 - radius;
//
//     sf::CircleShape circle(radius);
//     circle.setFillColor(sf::Color::Green); // задаем цвет
//
//     circle.setPosition(x, y);
//
//     window.clear();
//     window.draw(circle);
//     window.display();
// }

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600),
        "Pixel Poem");

    while (window.isOpen()) {
        sf::Event event = sf::Event();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // window.clear();
        window.display();

        sf::RectangleShape rectangle;
        rectangle.setPosition(sf::Vector2f(20, 20));
        rectangle.setSize({60, 180});
        rectangle.setFillColor(sf::Color(60, 60, 60));

        sf::CircleShape circleRed(25);
        circleRed.setPosition(sf::Vector2f(25, 25));
        circleRed.setFillColor(sf::Color(255, 0, 0));

        sf::CircleShape circleYellow(25);
        circleYellow.setPosition(sf::Vector2f(25, 85));
        circleYellow.setFillColor(sf::Color(255, 255, 0));

        sf::CircleShape circleGreen(25);
        circleGreen.setPosition(sf::Vector2f(25, 145));
        circleGreen.setFillColor(sf::Color(0, 255, 0));

        window.draw(rectangle);
        window.draw(circleRed);
        window.draw(circleYellow);
        window.draw(circleGreen);
    }

    std::cout << "@antllcon production" << std::endl;
    return 0;
}
