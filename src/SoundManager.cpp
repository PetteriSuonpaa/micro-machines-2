#include "SoundManager.hpp"
#include <iostream>

sf::Music SoundManager::music; // Static member initialization

void SoundManager::playMusic(const std::string& filePath, float volume) {
    // Load the music file
    if (!music.openFromFile(filePath))
        return ; // error

    // Set the volume
    music.setVolume(volume);

    // Play the music
    music.play();
}
