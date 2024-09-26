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

    sf::RectangleShape letterS0;
    letterS0.setFillColor(sf::Color(255, 255, 255));
    letterS0.setPosition(sf::Vector2f(200, 25));
    letterS0.setSize({60, 10});

    sf::RectangleShape letterS1;
    letterS1.setFillColor(sf::Color(255, 255, 255));
    letterS1.setPosition(sf::Vector2f(200, 25));
    letterS1.setSize({10, 90});

    sf::RectangleShape letterS2;
    letterS2.setFillColor(sf::Color(255, 255, 255));
    letterS2.setPosition(sf::Vector2f(200, 105));
    letterS2.setSize({60, 10});

    sf::RectangleShape letterS3;
    letterS3.setFillColor(sf::Color(255, 255, 255));
    letterS3.setPosition(sf::Vector2f(250, 65));
    letterS3.setSize({10, 40});

    sf::RectangleShape letterS4;
    letterS4.setFillColor(sf::Color(255, 255, 255));
    letterS4.setPosition(sf::Vector2f(230, 65));
    letterS4.setSize({20, 10});


    sf::RectangleShape letterG0;
    letterG0.setFillColor(sf::Color(255, 255, 255));
    letterG0.setPosition(sf::Vector2f(270, 25));
    letterG0.setSize({60, 10});

    sf::RectangleShape letterG1;
    letterG1.setFillColor(sf::Color(255, 255, 255));
    letterG1.setPosition(sf::Vector2f(270, 25));
    letterG1.setSize({10, 40});

    sf::RectangleShape letterG2;
    letterG2.setFillColor(sf::Color(255, 255, 255));
    letterG2.setPosition(sf::Vector2f(270, 65));
    letterG2.setSize({60, 10});


    sf::RectangleShape letterG3;
    letterG3.setFillColor(sf::Color(255, 255, 255));
    letterG3.setPosition(sf::Vector2f(320, 65));
    letterG3.setSize({10, 40});

    sf::RectangleShape letterG4;
    letterG4.setFillColor(sf::Color(255, 255, 255));
    letterG4.setPosition(sf::Vector2f(270, 105));
    letterG4.setSize({60, 10});


    sf::RectangleShape letterV0;
    letterV0.setFillColor(sf::Color(255, 255, 255));
    letterV0.setPosition(sf::Vector2f(340, 25));
    letterV0.rotate(-30);
    letterV0.setSize({10, 100});

    sf::RectangleShape letterV1;
    letterV1.setFillColor(sf::Color(255, 255, 255));
    letterV1.setPosition(sf::Vector2f(430, 25));
    letterV1.rotate(+30);
    letterV1.setSize({10, 100});


    sf::RectangleShape house;
    house.setFillColor(sf::Color(120, 30, 30));
    house.setPosition({300, 300});
    house.setSize({200, 100});

    sf::RectangleShape house1;
    house1.setFillColor(sf::Color(100, 30, 30));
    house1.setPosition({490, 300});
    house1.setSize({10, 100});

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(100, 30, 30));
    roof.setPosition({400, 270});
    roof.setPointCount(4);
    roof.setPoint(0,{-90, 0});
    roof.setPoint(1,{+90, 0});
    roof.setPoint(2,{+120, 40});
    roof.setPoint(3,{-120, 40});

    sf::RectangleShape door;
    door.setFillColor(sf::Color(10, 10, 10));
    door.setPosition({330, 330});
    door.setSize({40, 70});

    sf::RectangleShape windows;
    windows.setFillColor(sf::Color(200, 200, 240));
    windows.setPosition({400, 330});
    windows.setSize({50, 50});

    sf::RectangleShape roofDec;
    roofDec.setFillColor(sf::Color(60, 60, 60));
    roofDec.setPosition({400, 250});
    roofDec.setSize({20, 40});

    sf::RectangleShape roofDec2;
    roofDec2.setFillColor(sf::Color(70, 70, 70));
    roofDec2.setPosition({390, 250});
    roofDec2.setSize({20, 40});

    sf::RectangleShape roofDec3;
    roofDec3.setFillColor(sf::Color(70, 70, 70));
    roofDec3.setPosition({380, 230});
    roofDec3.setSize({50, 20});

    sf::RectangleShape roofDec4;
    roofDec4.setFillColor(sf::Color(60, 60, 60));
    roofDec4.setPosition({420, 230});
    roofDec4.setSize({10, 20});


    sf::CircleShape smoke(20);
    smoke.setFillColor(sf::Color(240, 240, 255));
    smoke.setPosition({330, 200});

    sf::CircleShape smoke1(18);
    smoke1.setFillColor(sf::Color(220, 220, 240));
    smoke1.setPosition({340, 195});

    sf::CircleShape smoke2(19);
    smoke2.setFillColor(sf::Color(200, 200, 210));
    smoke2.setPosition({355, 185});

    sf::CircleShape smoke3(15);
    smoke3.setFillColor(sf::Color(220, 220, 240));
    smoke3.setPosition({380, 190});


    sf::CircleShape smoke4(12);
    smoke4.setFillColor(sf::Color(220, 220, 240));
    smoke4.setPosition({400, 210});


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


        // Светофор
        window.draw(rectangle);
        window.draw(circleRed);
        window.draw(circleYellow);
        window.draw(circleGreen);

        window.draw(letterS0);
        window.draw(letterS1);
        window.draw(letterS2);
        window.draw(letterS3);
        window.draw(letterS4);

        window.draw(letterG0);
        window.draw(letterG1);
        window.draw(letterG2);
        window.draw(letterG3);
        window.draw(letterG4);

        window.draw(letterV0);
        window.draw(letterV1);

        window.draw(house);
        window.draw(house1);
        window.draw(roof);
        window.draw(door);
        window.draw(windows);

        window.draw(smoke);
        window.draw(smoke1);
        window.draw(smoke2);
        window.draw(smoke3);
        window.draw(smoke4);

        window.draw(roofDec);
        window.draw(roofDec2);
        window.draw(roofDec3);
        window.draw(roofDec4);



    }

    std::cout << "@antllcon production" << std::endl;
    return 0;
}
