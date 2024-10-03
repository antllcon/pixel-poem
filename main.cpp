#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    // Объявление констант
    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 600;
    constexpr float BALL_RADIUS = 40;

    sf::Vector2f speed = {150.f, -150.f};

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "Pixel Poem");
    sf::Clock clock;

    // шар
    sf::CircleShape circle(BALL_RADIUS);
    circle.setPosition(100, 200);
    circle.setFillColor(sf::Color(0, 255, 255));

    while (window.isOpen()) {
        sf::Event event = sf::Event();

        // конец игрового цикла - закрытие программы
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // работа со временем - шаг процессов
        const float deltaTime = clock.restart().asSeconds();
        sf::Vector2f position = circle.getPosition();

        position += speed * deltaTime;

        if ((position.x + 2 * BALL_RADIUS >= SCREEN_WIDTH) && (speed.x > 0)) {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0)) {
            speed.x = -speed.x;
        }
        if ((position.y + 2 * BALL_RADIUS >= SCREEN_HEIGHT) && (speed.y > 0)) {
            speed.y = -speed.y;
        }
        if ((position.y < 0) && (speed.y < 0)) {
            speed.y = -speed.y;
        }

        circle.setPosition(position);

        // рисование
        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
