#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Car.hpp"

class Game {
public:
    Game();
    void run(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    sf::Sprite& getBackgroundSprite();

private:
    static const int N = 5; // Number of cars
    float R;                // Car radius for collision detection
    float speed, angle;
    float maxSpeed, acc, dec, turnSpeed;
    int offsetX, offsetY;

    // SFML elements
    sf::Texture backgroundTexture, carTexture;
    sf::Sprite backgroundSprite, carSprite;

    // Cars
    Car car[N];

    // Game functions
    void processEvents();
    void updateCarMovement(bool Up, bool Down, bool Left, bool Right);
    void handleCollisions();
    void render();
};

#endif // GAME_HPP

