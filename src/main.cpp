#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "SoundManager.hpp"
#include "Game.hpp"
#include "OptionsMenu.hpp"
#include "PlayMenu.hpp"

using namespace sf;

int main() {
    RenderWindow menuWindow(VideoMode(1280, 720), "Main Menu");
    MainMenu mainMenu(menuWindow.getSize().x, menuWindow.getSize().y);
    Texture t3;
    t3.loadFromFile("images/hotline_miami.png");
    t3.setSmooth(true);
    Sprite MenuBackground(t3);
    SoundManager::playMusic("sounds/Michael Chen mainmenu song.ogg", SoundManager::getVolume());

    while (menuWindow.isOpen()) {
        Event event;
        while (menuWindow.pollEvent(event)) {
            if (event.type == Event::Closed)
                menuWindow.close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) mainMenu.MoveUp();
                if (event.key.code == Keyboard::Down) mainMenu.MoveDown();
                if (event.key.code == Keyboard::Return) {
                    int selectedItem = mainMenu.MainMenuPressed();

                    switch (selectedItem) {
                        case 0: { // Play
                            menuWindow.close();
                            RenderWindow playMenuWindow(VideoMode(1280, 720), "Select Map");
                            PlayMenu playMenu(playMenuWindow.getSize().x, playMenuWindow.getSize().y);

                            while (playMenuWindow.isOpen()) {
                                Event playEvent;
                                while (playMenuWindow.pollEvent(playEvent)) {
                                    if (playEvent.type == Event::Closed)
                                        playMenuWindow.close();
                                    if (playEvent.type == Event::KeyReleased) {
                                        if (playEvent.key.code == Keyboard::Up) playMenu.MoveUp();
                                        if (playEvent.key.code == Keyboard::Down) playMenu.MoveDown();
                                        if (playEvent.key.code == Keyboard::Return) {
                                            int selectedMap = playMenu.PlayMenuPressed();
                                            switch (selectedMap) {
                                                case 0: { // Map 1
                                                    playMenuWindow.close();
                                                    SoundManager::playMusic("sounds/Hotline Miami Soundtrack ~ Hydrogen [TubeRipper.cc].ogg", SoundManager::getVolume());
                                                    Game game(1280, 720); // Start the game
                                                    game.run();
                                                    SoundManager::stopMusic();
                                                    break;
                                                }
                                                case 1: { // Map 2
                                                    // Handle Map 2 selection (if needed in the future)
                                                    cout << "Map 2 is not implemented yet." << endl;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }

                                playMenuWindow.clear();
                                playMenu.draw(playMenuWindow);
                                playMenuWindow.display();
                            }
                            SoundManager::playMusic("sounds/Michael Chen mainmenu song.ogg", SoundManager::getVolume());
                            break;
                        }
                        case 1: { // Options
                            menuWindow.close();
                            OptionsMenu optionsMenu(1280, 720);
                            optionsMenu.open(menuWindow);
                            SoundManager::playMusic("sounds/Michael Chen mainmenu song.ogg", SoundManager::getVolume());
                            break;
                        }
                        case 2: { // About
                            // Handle about
                            break;
                        }
                        case 3: // Exit
                            menuWindow.close();
                            break;
                    }
                }
            }
        }

        menuWindow.clear();
        menuWindow.draw(MenuBackground);
        mainMenu.draw(menuWindow);
        menuWindow.display();
    }

    return 0;
}

