#include <gtest/gtest.h>
#include "OptionsMenu.hpp"
#include "OptionsMenu.cpp"
#include "SoundManager.hpp"
#include "SoundManager.cpp"
#include <SFML/Graphics.hpp>

// Test for OptionsMenu Initialization
TEST(OptionsMenuTests, Initialization) {
    OptionsMenu optionsMenu(1280, 720);

    // Check initial volume
    EXPECT_EQ(optionsMenu.getVolume(), 30);

    // Verify the volume bar's initial size
    sf::Vector2f expectedSize((30 / 100.f) * 400, 20); // 30% of 400
    EXPECT_EQ(optionsMenu.getVolumeBar().getSize(), expectedSize);
}

// Test volume increase functionality
TEST(OptionsMenuTests, IncreaseVolume) {
    OptionsMenu optionsMenu(1280, 720);

    // Simulate increasing the volume
    optionsMenu.adjustVolume(true); // Assume this calls Right key logic
    EXPECT_EQ(optionsMenu.getVolume(), 35);

    // Check that the volume bar updates accordingly
    sf::Vector2f expectedSize((35 / 100.f) * 400, 20);
    EXPECT_EQ(optionsMenu.getVolumeBar().getSize(), expectedSize);
}

// Test volume decrease functionality
TEST(OptionsMenuTests, DecreaseVolume) {
    OptionsMenu optionsMenu(1280, 720);

    // Simulate decreasing the volume
    optionsMenu.adjustVolume(false); // Assume this calls Left key logic
    EXPECT_EQ(optionsMenu.getVolume(), 25);

    // Check that the volume bar updates accordingly
    sf::Vector2f expectedSize((25 / 100.f) * 400, 20);
    EXPECT_EQ(optionsMenu.getVolumeBar().getSize(), expectedSize);
}

// Test volume boundaries
TEST(OptionsMenuTests, VolumeBoundaries) {
    OptionsMenu optionsMenu(1280, 720);

    // Set volume to 0 and try decreasing further
    optionsMenu.setVolume(0);
    optionsMenu.adjustVolume(false); // Left key
    EXPECT_EQ(optionsMenu.getVolume(), 0); // Should remain at 0

    // Set volume to 100 and try increasing further
    optionsMenu.setVolume(100);
    optionsMenu.adjustVolume(true); // Right key
    EXPECT_EQ(optionsMenu.getVolume(), 100); // Should remain at 100
}

// Test SoundManager integration
TEST(OptionsMenuTests, SoundManagerIntegration) {
    OptionsMenu optionsMenu(1280, 720);

    // Adjust volume and check SoundManager updates
    optionsMenu.adjustVolume(true); // Increase volume
    EXPECT_EQ(SoundManager::getVolume(), optionsMenu.getVolume());

    optionsMenu.adjustVolume(false); // Decrease volume
    EXPECT_EQ(SoundManager::getVolume(), optionsMenu.getVolume());
}

// Test graphical updates (basic sanity check)
TEST(OptionsMenuTests, UpdateVolumeDisplay) {
    OptionsMenu optionsMenu(1280, 720);

    // Adjust volume and ensure no exceptions occur during display updates
    EXPECT_NO_THROW(optionsMenu.updateVolumeDisplay());
}
