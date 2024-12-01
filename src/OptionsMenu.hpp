#ifndef OPTIONSMENU_HPP
#define OPTIONSMENU_HPP

#include <SFML/Graphics.hpp>
#include "SoundManager.hpp"

class OptionsMenu {
public:
    OptionsMenu(float width, float height);
    void open(sf::RenderWindow& parentWindow);  // Open the Options Menu
private:
    int volume;  // Current volume level
    sf::Font font;
    sf::Text instructionText;
    sf::RectangleShape volumeBarBackground;  // Background bar
    sf::RectangleShape volumeBar;           // Active volume bar

    void updateVolumeDisplay();  // Helper to update volume text
};

#endif