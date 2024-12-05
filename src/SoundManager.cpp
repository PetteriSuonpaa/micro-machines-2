#include "SoundManager.hpp"

sf::Music SoundManager::music;
sf::SoundBuffer SoundManager::soundBuffer;
sf::Sound SoundManager::sound;
int SoundManager::currentVolume = 30; // Default volume

void SoundManager::playMusic(const std::string& filename, int volume) {
    if (!music.openFromFile(filename)) {
        throw std::runtime_error("Failed to load music file");
    }
    currentVolume = volume; // Update the global volume
    music.setVolume(static_cast<float>(currentVolume));
    music.setLoop(true);
    music.play();
}

void SoundManager::stopMusic() {
    music.stop();
}

void SoundManager::setVolume(int volume) {
    currentVolume = volume;
    music.setVolume(static_cast<float>(currentVolume));
    sound.setVolume(static_cast<float>(currentVolume));
}

int SoundManager::getVolume() {
    return currentVolume;
}

void SoundManager::playSound(const std::string& filename) {
    if (!soundBuffer.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load sound file");
    }
    sound.setBuffer(soundBuffer);
    sound.setVolume(static_cast<float>(currentVolume));
    sound.play();
}