#include "PlayMenu.hpp"
sf::Color Purple(128, 0, 128);

PlayMenu::PlayMenu(float width, float height) 
{
    if (!font.loadFromFile("Fonts/Freedom-10eM.ttf")) {
        cout << "No font is here";
    }

    // Load map preview images
    if (!mapTextures[0].loadFromFile("images/background.png")) {
        cout << "Failed to load background image for Map 1" << endl;
    }
    if (!mapTextures[1].loadFromFile("images/micro-machines-2-turbo-tournament-driller-killer-game-gear-map.png")) {
        cout << "Failed to load background image for Map 2" << endl;
    }

    // Initialize map preview sprite with the first map
    mapPreview.setTexture(mapTextures[0]);
    mapPreview.setScale(1.0f, 1.0f); // Adjust as necessary for window size
    mapPreview.setPosition(0, 0);    // Fullscreen background

    // Map 1
    playMenu[0].setFont(font);
    playMenu[0].setFillColor(Color::White);
    playMenu[0].setString("Chainsaw Chase");
    playMenu[0].setCharacterSize(70);
    playMenu[0].setPosition(500, 300);

    // Map 2
    playMenu[1].setFont(font);
    playMenu[1].setFillColor(Color::White);
    playMenu[1].setString("Driller Killer");
    playMenu[1].setCharacterSize(70);
    playMenu[1].setPosition(500, 400);

    PlayMenuSelected = 0;
    playMenu[PlayMenuSelected].setFillColor(Purple);
}

PlayMenu::~PlayMenu() {}

// Draw PlayMenu
void PlayMenu::draw(RenderWindow& Window) {
    // Draw the current map background first
    Window.draw(mapPreview);

    // Draw the menu items on top of the background
    for (int i = 0; i < Max_play_menu; ++i) {
        Window.draw(playMenu[i]);
    }
}

// Move Up
void PlayMenu::MoveUp()
{
    playMenu[PlayMenuSelected].setFillColor(Color::White);

    PlayMenuSelected--;
    if (PlayMenuSelected < 0) {
        PlayMenuSelected = Max_play_menu - 1;
    }

    playMenu[PlayMenuSelected].setFillColor(Purple);

    // Update the background to the currently selected map
    mapPreview.setTexture(mapTextures[PlayMenuSelected]);
}

// Move Down
void PlayMenu::MoveDown()
{
    playMenu[PlayMenuSelected].setFillColor(Color::White);

    PlayMenuSelected++;
    if (PlayMenuSelected >= Max_play_menu) {
        PlayMenuSelected = 0;
    }

    playMenu[PlayMenuSelected].setFillColor(Purple);

    // Update the background to the currently selected map
    mapPreview.setTexture(mapTextures[PlayMenuSelected]);
}
