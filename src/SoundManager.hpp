#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>

class SoundManager {
public:
    static void playMusic(const std::string& filename, int volume = 30);
    static void stopMusic();
    static void setVolume(int volume);
    static int getVolume(); // New getter for current volume

    static void playSound(const std::string& filename);

private:
    static sf::Music music;
    static sf::SoundBuffer soundBuffer;
    static sf::Sound sound;
    static int currentVolume; // Store current volume globally
};

#endif