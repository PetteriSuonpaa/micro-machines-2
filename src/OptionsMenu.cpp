#include "OptionsMenu.hpp"
#include <string>

OptionsMenu::OptionsMenu(float width, float height) : volume(30) {
    // Load font
    if (!font.loadFromFile("Fonts/Freedom-10eM.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Set up instructions
    instructionText.setFont(font);
    instructionText.setCharacterSize(25);
    instructionText.setFillColor(sf::Color::Cyan);
    instructionText.setPosition(80, 300);
    instructionText.setString("Sound: Use Left/Right to Adjust, Esc to Return");

    // Set up volume bar background
    volumeBarBackground.setSize(sf::Vector2f(400, 20));  // Fixed width
    volumeBarBackground.setFillColor(sf::Color::White);
    volumeBarBackground.setPosition(100, 150);

    // Set up active volume bar
    volumeBar.setSize(sf::Vector2f(120, 20));  // Starts with 30% of 400
    volumeBar.setFillColor(sf::Color::Green);
    volumeBar.setPosition(100, 150);
}

#include "OptionsMenu.hpp"
#include "SoundManager.hpp"

void OptionsMenu::open(sf::RenderWindow& parentWindow) {
    sf::RenderWindow optionsWindow(sf::VideoMode(1280, 720), "Options");
    while (optionsWindow.isOpen()) {
        sf::Event event;
        while (optionsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                optionsWindow.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left && volume > 0) {
                    volume -= 5;
                } else if (event.key.code == sf::Keyboard::Right && volume < 100) {
                    volume += 5;
                }
                SoundManager::setVolume(volume); // Update the global volume
                updateVolumeDisplay();
            }
        }

        optionsWindow.clear();
        optionsWindow.draw(volumeBarBackground);
        optionsWindow.draw(volumeBar);
        optionsWindow.draw(instructionText);
        optionsWindow.display();
    }

    // Close options window and return to the parent menu
    parentWindow.create(sf::VideoMode(1280, 720), "Main Menu");
}
void OptionsMenu::updateVolumeDisplay() {
    // Scale the active volume bar width based on the volume percentage
    volumeBar.setSize(sf::Vector2f((volume / 100.f) * 400, 20));
}