#pragma once
#include <SFML/Graphics/Rect.hpp>

#include "core/config.h"
#include "systems/Sound/SoundManager.h"

inline sf::FloatRect addFloatRects(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    return sf::FloatRect(
        rect1.left + rect2.left,   // Сложение координат X
        rect1.top + rect2.top,     // Сложение координат Y
        rect1.width + rect2.width, // Сложение ширин
        rect1.height + rect2.height // Сложение высот
    );
}

inline void initializeSounds() {
    SoundManager& soundManager = SoundManager::getInstance();

    // Загрузка звуков
    soundManager.loadSound(SoundEffect::Fire, SOUND_FIRE);

    // Загрузка музыки
    soundManager.loadMusic(MUSIC_GAME);
}
