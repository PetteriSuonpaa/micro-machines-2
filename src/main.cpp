#include <SFML/Graphics.hpp>
#include <MainMenu.hpp>
#include <SoundManager.hpp>
#include "Game.hpp"
using namespace sf;
int main() {
    RenderWindow menuWindow(VideoMode(1280, 720), "Main Menu");
    MainMenu mainMenu(menuWindow.getSize().x, menuWindow.getSize().y);
    Texture t3;
    t3.loadFromFile("images/hotline_miami.png");
    t3.setSmooth(true);
    Sprite MenuBackground(t3);

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
                            SoundManager::playMusic("sounds/Hotline Miami Soundtrack ~ Hydrogen [TubeRipper.cc].ogg");
                            Game game(1280, 720);
                            game.run();
                            SoundManager::stopMusic();
                            break;
                        }
                        case 1: { // Options
                            // Handle options
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
        // Draw menu
        menuWindow.draw(MenuBackground);
        mainMenu.draw(menuWindow);
        menuWindow.display();
    }

    return 0;
}
