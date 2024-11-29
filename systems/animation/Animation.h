#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
   public:
    Animation(float animationSpeed);

    void addFrame(const sf::Texture& texture);
    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite);
    void reset();

   private:
    std::vector<sf::Texture> frames;
    float animationSpeed;
    float elapsedTime;
    size_t currentFrame;
};
