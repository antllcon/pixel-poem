#include "CameraManager.h"

CameraManager::CameraManager(float screenWidth, float screenHeight, float cameraDeltaWidth, float cameraDeltaHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), cameraDeltaWidth(cameraDeltaWidth), cameraDeltaHeight(cameraDeltaHeight) {}

CameraManager::~CameraManager() = default;

void CameraManager::update(sf::View& view, const Player* player) {
    if (!player) return;

    float cameraLeft = view.getCenter().x - cameraDeltaWidth;
    float cameraRight = view.getCenter().x + cameraDeltaWidth;
    float cameraTop = view.getCenter().y - cameraDeltaHeight;
    float cameraBottom = view.getCenter().y + cameraDeltaHeight;

    if (player->getX() < cameraLeft) {
        view.move(player->getX() - cameraLeft, 0);
    }
    if (player->getX() > cameraRight) {
        view.move(player->getX() - cameraRight, 0);
    }
    if (player->getY() < cameraTop) {
        view.move(0, player->getY() - cameraTop);
    }
    if (player->getY() > cameraBottom) {
        view.move(0, player->getY() - cameraBottom);
    }
}

void CameraManager::reset(sf::View& view) {
    view.setCenter(screenWidth / 2.0f, screenHeight / 2.0f);
}
