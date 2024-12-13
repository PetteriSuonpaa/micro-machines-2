#include <gtest/gtest.h>
#include "SoundManager.hpp"
#include "SoundManager.cpp"

// Test for playing music
TEST(SoundManagerTests, PlayMusic) {
    // Ensure no exceptions are thrown when playing valid music
    EXPECT_NO_THROW(SoundManager::playMusic("sounds/test_music.ogg", 50));

    // Verify that the volume is correctly set
    EXPECT_EQ(SoundManager::getVolume(), 50);
}

// Test for stopping music
TEST(SoundManagerTests, StopMusic) {
    // Play music first
    SoundManager::playMusic("sounds/test_music.ogg", 30);

    // Stop music and verify
    EXPECT_NO_THROW(SoundManager::stopMusic());
}

// Test for setting volume
TEST(SoundManagerTests, SetVolume) {
    SoundManager::setVolume(75);
    EXPECT_EQ(SoundManager::getVolume(), 75);

    SoundManager::setVolume(0);
    EXPECT_EQ(SoundManager::getVolume(), 0);

    SoundManager::setVolume(100);
    EXPECT_EQ(SoundManager::getVolume(), 100);
}

// Test volume boundaries
TEST(SoundManagerTests, VolumeBoundaries) {
    // Set volume to a negative value
    SoundManager::setVolume(-10);
    EXPECT_EQ(SoundManager::getVolume(), 0); // Should be clamped to 0

    // Set volume above the maximum
    SoundManager::setVolume(120);
    EXPECT_EQ(SoundManager::getVolume(), 100); // Should be clamped to 100
}

// Test for playing sound effects
TEST(SoundManagerTests, PlaySound) {
    // Ensure no exceptions are thrown when playing valid sound
    EXPECT_NO_THROW(SoundManager::playSound("sounds/test_sound.ogg"));

    // Check if the sound plays at the correct volume
    EXPECT_EQ(SoundManager::getVolume(), 30); // Assuming default volume
}

// Test sound playback failure for invalid file
TEST(SoundManagerTests, PlaySoundInvalidFile) {
    EXPECT_THROW(SoundManager::playSound("invalid_file.ogg"), std::runtime_error);
}

// Test music playback failure for invalid file
TEST(SoundManagerTests, PlayMusicInvalidFile) {
    EXPECT_THROW(SoundManager::playMusic("invalid_file.ogg", 50), std::runtime_error);
}
