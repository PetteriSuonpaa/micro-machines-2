#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// Define the maximum number of play menu items
#define Max_play_menu 2

class PlayMenu
{
private:
    int PlayMenuSelected;
    Font font;
    Text playMenu[Max_play_menu];
    Texture mapTextures[Max_play_menu];
    Sprite mapPreview;

public: 
    PlayMenu(float width, float height);
    void draw(RenderWindow& Window);
    void MoveUp();
    void MoveDown();

    int PlayMenuPressed() {
        return PlayMenuSelected;
    }
    ~PlayMenu();
};
