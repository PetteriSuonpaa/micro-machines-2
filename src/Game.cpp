#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Game::Game()
    : maxSpeed(12.0), acc(0.2), dec(0.3), turnSpeed(0.08), speed(0), angle(0), offsetX(0), offsetY(0) {
    if (!backgroundTexture.loadFromFile("images/background.png") ||
        !carTexture.loadFromFile("images/car.png")) {
        std::cerr << "Error loading textures!" << std::endl;
    }

    backgroundTexture.setSmooth(true);
    carTexture.setSmooth(true);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.scale(2, 2);

    carSprite.setTexture(carTexture);
    carSprite.setOrigin(22, 22); // Set origin for rotation
    R = 22; // Car radius for collision detection

    for (int i = 0; i < N; ++i) {
        car[i].x = 300 + i * 50;
        car[i].y = 1700 + i * 80;
        car[i].speed = 7 + i;
    }
}
sf::Sprite& Game::getBackgroundSprite() {
    return backgroundSprite;
}

void Game::run(sf::RenderWindow& window) {
        bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

        updateCarMovement(Up, Down, Left, Right);
        handleCollisions();
        render(window);
}

void Game::updateCarMovement(bool Up, bool Down, bool Left, bool Right) {
    
    if (Up && speed < maxSpeed) {
        speed += (speed < 0) ? dec : acc;
    }
    if (Down && speed > -maxSpeed) {
        speed -= (speed > 0) ? dec : acc;
    }
    if (!Up && !Down) {
        if (speed > 0) speed -= dec;
        else if (speed < 0) speed += dec;
        else speed = 0;
    }

    if (Right && speed != 0) angle += turnSpeed * (speed / maxSpeed);
    if (Left && speed != 0) angle -= turnSpeed * (speed / maxSpeed);

    car[0].speed = speed;
    car[0].angle = angle;

    for (int i = 0; i < N; ++i) car[i].move();
    for (int i = 1; i < N; ++i) car[i].findTarget();
}

void Game::handleCollisions() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int dx = 0, dy = 0;
            while (dx * dx + dy * dy < 4 * R * R) {
                car[i].x += dx / 10.0;
                car[i].y += dy / 10.0;
                car[j].x -= dx / 10.0;
                car[j].y -= dy / 10.0;

                dx = car[i].x - car[j].x;
                dy = car[i].y - car[j].y;
                if (!dx && !dy) break;
            }
        }
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear(sf::Color::White);

    if (car[0].x > 320) offsetX = car[0].x - 320;
    if (car[0].y > 240) offsetY = car[0].y - 240;

    backgroundSprite.setPosition(-offsetX, -offsetY);
    window.draw(backgroundSprite);

    sf::Color colors[10] = {sf::Color::Red, sf::Color::Green, sf::Color::Magenta, sf::Color::Blue, sf::Color::White};
    for (int i = 0; i < N; ++i) {
        carSprite.setPosition(car[i].x - offsetX, car[i].y - offsetY);
        carSprite.setRotation(car[i].angle * 180 / 3.141593);
        carSprite.setColor(colors[i]);
        window.draw(carSprite);
    }

    window.display();
}