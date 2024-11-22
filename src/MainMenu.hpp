#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// Define the maximum number of menu items
#define Max_main_menu 4



class MainMenu 
{
private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];


public:
    MainMenu(float width, float height);
    void draw(RenderWindow& Window);
    void MoveUp();
    void MoveDown();

    int MainMenuPressed(){
        return MainMenuSelected;
    }
    ~MainMenu();

};
