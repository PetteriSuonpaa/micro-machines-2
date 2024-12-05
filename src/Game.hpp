#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Car.hpp>
#include <SoundManager.hpp>
#include <vector>

class Game {
private:
    sf::RenderWindow gameWindow;
    sf::Texture bgTexture, carTexture, iconTexture;
    sf::Sprite sBackground, sCar, boostIcon;
    sf::RectangleShape boostSlider;
    std::vector<Car> cars;

    float speed;
    float angle;
    int offsetX, offsetY;

    static constexpr float maxSpeed = 12.0f;
    static constexpr float acc = 0.2f;
    static constexpr float deceleration = 0.3f;
    static constexpr float turnSpeed = 0.08f;
    static constexpr float R = 22.0f; // Car radius
    static constexpr int N = 5; // Number of cars

    // Boost-related variables
    float boostMultiplier;          // Multiplier for speedboost
    float boostDuration;
    float boostCooldown;
    bool isBoosting;                // boost is active?
    bool boostAvailable;            // boost is ready to use?
    sf::Clock boostClock;           // Clock to manage boost cooldown and duration
    sf::Clock cooldownClock;        // Clock to track cooldown

    void handleCarMovement();
    void checkCollisions();
    void render();
    void updateBoostVisuals();

    // Boost-related functions
    void activateBoost();
    void deactivateBoost();

public:
    Game(float windowWidth, float windowHeight);
    void run();
};

#endif // GAME_HPP
