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
    sf::Texture bgTexture, carTexture;
    sf::Sprite sBackground, sCar;
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

    void handleCarMovement();
    void checkCollisions();
    void render();

public:
    Game(float windowWidth, float windowHeight);
    void run();
};

#endif // GAME_HPP
