#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include <unordered_map>

enum class SoundEffect {
    Fire
};

class SoundManager {
public:
    static SoundManager& getInstance();

    void loadSound(SoundEffect effect, const std::string& filepath);
    void playSound(SoundEffect effect);

    void loadMusic(const std::string& filepath);
    void playMusic(bool loop = true);
    void stopMusic();

private:
    SoundManager() = default;
    ~SoundManager() = default;

    std::unordered_map<SoundEffect, sf::SoundBuffer> soundBuffers;
    std::unordered_map<SoundEffect, sf::Sound> sounds;
    sf::Music music;
};
