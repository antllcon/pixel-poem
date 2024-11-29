#pragma once
#include <SFML/Graphics.hpp>
#include "../../entities/player/Player.h"

class CameraManager {
public:
    CameraManager(float screenWidth, float screenHeight, float cameraDeltaWidth, float cameraDeltaHeight);
    ~CameraManager();

    void update(sf::View& view, const Player* player);
    void reset(sf::View& view);

private:
    float screenWidth;
    float screenHeight;
    float cameraDeltaWidth;
    float cameraDeltaHeight;
};
