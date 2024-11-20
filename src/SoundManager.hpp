#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <string>

class SoundManager {
public:
    // Function to play the soundtrack
    static void playMusic(const std::string& filePath, float volume = 30.f);

private:
    // Static sf::Music instance to manage music playback
    static sf::Music music;
};

#endif 