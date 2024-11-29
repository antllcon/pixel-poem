#include "Animation.h"

Animation::Animation(float animationSpeed)
    : animationSpeed(animationSpeed), elapsedTime(0.f), currentFrame(0) {}

void Animation::addFrame(const sf::Texture& texture) {
    frames.push_back(texture);
}

void Animation::update(float deltaTime) {
    if (frames.empty()) return;

    elapsedTime += deltaTime;
    if (elapsedTime >= animationSpeed) {
        elapsedTime = 0.f;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

void Animation::applyToSprite(sf::Sprite& sprite) {
    if (!frames.empty()) {
        sprite.setTexture(frames[currentFrame]);
    }
}

void Animation::reset() {
    elapsedTime = 0.f;
    currentFrame = 0;
}
