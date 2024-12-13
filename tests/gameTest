#include <gtest/gtest.h>
#include "Game.hpp"
#include "Game.cpp"
#include "SoundManager.hpp"
#include "SoundManager.cpp"
#include <SFML/Graphics.hpp>

// Mock class for SoundManager to prevent actual file loading during tests
class MockSoundManager {
public:
    static void playSound(const std::string&) {}
};

// Replace the real SoundManager with the mock in tests
using SoundManager = MockSoundManager;

// Test initialization of the game
TEST(GameTests, Initialization) {
    Game game(1280, 720);

    // Verify game window properties
    EXPECT_EQ(game.getWindowWidth(), 1280);
    EXPECT_EQ(game.getWindowHeight(), 720);

    // Check boost initial states
    EXPECT_FALSE(game.isBoostingActive());
    EXPECT_TRUE(game.isBoostAvailable());

    // Check car properties
    const auto& cars = game.getCars();
    EXPECT_EQ(cars.size(), Game::N);
    EXPECT_EQ(cars[0].speed, 7);
}

// Test boost activation
TEST(GameTests, ActivateBoost) {
    Game game(1280, 720);

    // Ensure boost is initially available
    EXPECT_TRUE(game.isBoostAvailable());

    // Activate boost
    game.handleInput(true, false, false, false, true); // Boost key pressed
    EXPECT_TRUE(game.isBoostingActive());
    EXPECT_FALSE(game.isBoostAvailable());

    // Verify speed is multiplied
    float expectedSpeed = game.getMaxSpeed() * game.getBoostMultiplier();
    EXPECT_FLOAT_EQ(game.getSpeed(), expectedSpeed);
}

// Test boost deactivation
TEST(GameTests, DeactivateBoost) {
    Game game(1280, 720);
    game.handleInput(true, false, false, false, true); // Activate boost

    // Simulate boost duration elapsed
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < game.getBoostDuration() + 0.1f) {}

    game.updateBoostVisuals();
    EXPECT_FALSE(game.isBoostingActive());
    EXPECT_FALSE(game.isBoostAvailable());
}

// Test boost cooldown
TEST(GameTests, BoostCooldown) {
    Game game(1280, 720);
    game.handleInput(true, false, false, false, true); // Activate boost

    // Simulate boost duration and cooldown
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < game.getBoostCooldown() + 0.1f) {}

    game.updateBoostVisuals();
    EXPECT_TRUE(game.isBoostAvailable());
}

// Test car movement
TEST(GameTests, CarMovement) {
    Game game(1280, 720);

    // Simulate forward movement
    game.handleInput(true, false, false, false, false); // Up key pressed
    float initialX = game.getCars()[0].x;
    float initialY = game.getCars()[0].y;

    game.updateGameLogic();
    EXPECT_GT(game.getCars()[0].x, initialX);
    EXPECT_LT(game.getCars()[0].y, initialY); // Moving upward
}

// Test collision handling
TEST(GameTests, CollisionDetection) {
    Game game(1280, 720);

    // Set two cars at the same position to simulate a collision
    auto& cars = game.getCars();
    cars[0].setPosition(300, 300);
    cars[1].setPosition(300, 300);

    game.checkCollisions();

    // Ensure the cars are separated after collision handling
    EXPECT_NE(cars[0].x, cars[1].x);
    EXPECT_NE(cars[0].y, cars[1].y);
}

// Test rendering logic
TEST(GameTests, RenderLogic) {
    Game game(1280, 720);

    // Call render to ensure no crashes or errors
    ASSERT_NO_THROW(game.render());
}

// Test handling input for movement and boost
TEST(GameTests, HandleInput) {
    Game game(1280, 720);

    // Test forward movement
    game.handleInput(true, false, false, false, false); // Up key pressed
    EXPECT_GT(game.getSpeed(), 0);

    // Test backward movement
    game.handleInput(false, true, false, false, false); // Down key pressed
    EXPECT_LT(game.getSpeed(), 0);

    // Test turning
    game.handleInput(false, false, true, false, false); // Left key pressed
    EXPECT_LT(game.getAngle(), 0);

    game.handleInput(false, false, false, true, false); // Right key pressed
    EXPECT_GT(game.getAngle(), 0);
}
