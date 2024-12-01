#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>

class SoundManager {
public:
    static void playMusic(const std::string& filename, int volume = 30);
    static void stopMusic();
    static void setVolume(int volume);
    static int getVolume(); // New getter for current volume

private:
    static sf::Music music;
    static int currentVolume; // Store current volume globally
};

#endif