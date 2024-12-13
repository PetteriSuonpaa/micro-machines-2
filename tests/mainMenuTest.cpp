#include "MainMenu.hpp"
#include "MainMenu.cpp"
#include <gtest/gtest.h>

// Test for initial state of the MainMenu
TEST(MainMenuTests, InitialState) {
    MainMenu mainMenu(1280, 720);

    // Test that the initial selection is the first item
    EXPECT_EQ(mainMenu.MainMenuPressed(), 0);
}

// Test navigation upwards
TEST(MainMenuTests, MoveUp) {
    MainMenu mainMenu(1280, 720);

    // Move up from the initial position (0)
    mainMenu.MoveUp();
    EXPECT_EQ(mainMenu.MainMenuPressed(), 3); // Wraps around to the last item

    // Move up again
    mainMenu.MoveUp();
    EXPECT_EQ(mainMenu.MainMenuPressed(), 2);
}

// Test navigation downwards
TEST(MainMenuTests, MoveDown) {
    MainMenu mainMenu(1280, 720);

    // Move down from the initial position (0)
    mainMenu.MoveDown();
    EXPECT_EQ(mainMenu.MainMenuPressed(), 1);

    // Move down again
    mainMenu.MoveDown();
    EXPECT_EQ(mainMenu.MainMenuPressed(), 2);
}

// Test for initial state of the MainMenu
TEST(MainMenuTests, InitialState) {
    MainMenu mainMenu(1280, 720);

    // Test that the initial selection is the first item
    EXPECT_EQ(mainMenu.MainMenuPressed(), 0);
}

// Test navigation upwards
TEST(MainMenuTests, MoveUp) {
    MainMenu mainMenu(1280, 720);

    // Move up from the initial position (0)
    mainMenu.MoveUp();
    EXPECT_EQ(mainMenu.MainMenuPressed(), 3); // Wraps around to the last item

    // Move up again
    mainMenu.MoveUp();
    EXPECT_EQ(mainMenu.MainMenuPressed(), 2);
}

// Test navigation downwards
TEST(MainMenuTests, MoveDown) {
    MainMenu mainMenu(1280, 720);

    // Move down from the initial position (0)
    mainMenu.MoveDown();
    EXPECT_EQ(mainMenu.MainMenuPressed(), 1);

    // Move down again
    mainMenu.MoveDown();
    EXPECT_EQ(mainMenu.MainMenuPressed(), 2);
}

// Test wrap-around navigation
TEST(MainMenuTests, WrapAroundNavigation) {
    MainMenu mainMenu(1280, 720);

    // Move down multiple times to ensure wrap-around
    for (int i = 0; i < 5; ++i) {
        mainMenu.MoveDown();
    }
    EXPECT_EQ(mainMenu.MainMenuPressed(), 1); // Wraps around to 1

    // Move up multiple times to ensure wrap-around
    for (int i = 0; i < 5; ++i) {
        mainMenu.MoveUp();
    }
    EXPECT_EQ(mainMenu.MainMenuPressed(), 3); // Wraps around to 3
}

// Test menu drawing (basic sanity check)
TEST(MainMenuTests, DrawMenu) {
    MainMenu mainMenu(1280, 720);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Test Window");
    EXPECT_NO_THROW(mainMenu.draw(window)); // Ensure draw does not throw exceptions
}(MainMenuTests, WrapAroundNavigation) {
    MainMenu mainMenu(1280, 720);

    // Move down multiple times to ensure wrap-around
    for (int i = 0; i < 5; ++i) {
        mainMenu.MoveDown();
    }
    EXPECT_EQ(mainMenu.MainMenuPressed(), 1); // Wraps around to 1

    // Move up multiple times to ensure wrap-around
    for (int i = 0; i < 5; ++i) {
        mainMenu.MoveUp();
    }
    EXPECT_EQ(mainMenu.MainMenuPressed(), 3); // Wraps around to 3
}

// Test menu drawing (basic sanity check)
TEST(MainMenuTests, DrawMenu) {
    MainMenu mainMenu(1280, 720);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Test Window");
    EXPECT_NO_THROW(mainMenu.draw(window)); // Ensure draw does not throw exceptions
}