#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::loadSound(SoundEffect effect, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load sounds: " << filepath << std::endl;
        return;
    }

    soundBuffers[effect] = buffer;
    sf::Sound sound;
    sound.setBuffer(soundBuffers[effect]);
    sounds[effect] = sound;
}

void SoundManager::playSound(SoundEffect effect) {
    if (sounds.find(effect) != sounds.end()) {
        sounds[effect].play();
    } else {
        std::cerr << "Sound not found for effect ID: " << static_cast<int>(effect) << std::endl;
    }
}
void SoundManager::loadMusic(const std::string& filepath) {
    if (!music.openFromFile(filepath)) {
        std::cerr << "Failed to load music: " << filepath << std::endl;
    }
}

void SoundManager::playMusic(bool loop) {
    music.setLoop(loop);
    music.play();
}

void SoundManager::stopMusic() {
    music.stop();
}
