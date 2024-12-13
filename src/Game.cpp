#include "Game.hpp"
#include <iostream>
using namespace std;
using namespace sf;
Game::Game(float windowWidth, float windowHeight)
    : gameWindow(sf::VideoMode(windowWidth, windowHeight), "Car Racing Game"),
      speed(0), angle(0), offsetX(0), offsetY(0),
      // Speed boost variables:
      boostMultiplier(2.0f), boostDuration(2.5), boostCooldown(5.0f),
      isBoosting(false), boostAvailable(true) {
    // Load textures
    bgTexture.loadFromFile("images/background.png");
    carTexture.loadFromFile("images/car.png");
    iconTexture.loadFromFile("images/boost_icon.png");

    if (!font.loadFromFile("Fonts/Freedom-10eM.ttf")){
        cout <<"No font is here";

    }
    // Load the sound in the constructor
    if (!oilSpillSoundBuffer.loadFromFile("sounds/113365__silversatyr__fall.ogg")) {
        std::cout << "Error loading oil spill sound!" << std::endl;
    } else {
        oilSpillSound.setBuffer(oilSpillSoundBuffer);
        oilSpillSound.setVolume(20); // Adjust volume 
    }
    //out of Bounds text
    outOfBoundText.setFont(font);
    outOfBoundText.setString("Out of Bound!");
    outOfBoundText.setCharacterSize(50);
    outOfBoundText.setFillColor(sf::Color::Red);
    outOfBoundText.setPosition(400, 50); // Position on the screen
    outOfBoundText.setStyle(sf::Text::Bold);
    // Setup sprites
    sBackground.setTexture(bgTexture);
    sBackground.scale(2, 2);
    carTexture.setSmooth(true);
    sCar.setTexture(carTexture);
    sCar.setOrigin(R, R);
    boostIcon.setTexture(iconTexture);
    boostIcon.setPosition(10, 10);
    boostIcon.setScale(0.2f, 0.2f);

    // Setup boost slider
    boostSlider.setSize(sf::Vector2f(100, 10));
    boostSlider.setFillColor(sf::Color::Green);
    boostSlider.setPosition(10, 125); // Below the icon

    // Initialize cars
    for (int i = 0; i < N; ++i) {
        Car car;
        car.x = 300 + i * 50;
        car.y = 1700 + i * 80;
        car.speed = 5 + i;
        cars.push_back(car);
    }

    gameWindow.setFramerateLimit(60);

    boostClock.restart();
}

void Game::run() {
    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                gameWindow.close();
            }
        }

        checkOilSpillCollision(cars[0].x, cars[0].y);  // Pass player's car position
        handleCarMovement();
        updateBoostVisuals();
        checkCollisions();
        render();
    }
}
// Function to check if the car is within the track's boundaries
bool Game::isOnTrack(float x, float y) {
    for (const auto& rect : trackBounds) {
        if (rect.contains(x, y)) {
            return true; // Car is on the track
        }
    }
    return false; // Car is off the track
}
void Game::checkOilSpillCollision(float x, float y) {
    for (const auto& rect : oilSpillBounds) {
        if (rect.contains(x, y)) {
            std::cout << "Collision detected at: (" << x << ", " << y << ")" << std::endl;
            oilSpillSound.play(); // This will play the oil spill sound
            // Start the spinning effect if it's not already spinning
            if (!isSpinning) {
                isSpinning = true;
                oilSpinClock.restart();  // Restart the clock when the collision happens
                cars[0].speed *= 0.5f;  // Reduce speed to simulate slip
            }

            return; // Only process one spill at a time
        }
    }

    std::cout << "No collision detected for position: (" << x << ", " << y << ")" << std::endl;
}
void Game::handleCarMovement() {
    bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool Boost = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    // Handle speed boost
    if (Boost && boostAvailable) {
        activateBoost();
    }

    if (isBoosting && boostClock.getElapsedTime().asSeconds() >= boostDuration) {
        deactivateBoost();
    }

    // Update speed with boost multiplier
    float effectiveMaxSpeed = isBoosting ? maxSpeed * boostMultiplier : maxSpeed;

    // Calculate new position based on speed and angle
    float newX = cars[0].x + cos(angle * 3.14159 / 180.0f) * speed;
    float newY = cars[0].y + sin(angle * 3.14159 / 180.0f) * speed;
    if (isSpinning) {
        // Check if 3 seconds have passed
        if (oilSpinClock.getElapsedTime().asSeconds() >= 1.0f) {
            isSpinning = false;  // Stop spinning after 3 seconds
        } else {
            // Apply continuous spinning during the 3 seconds
            angle += 50;  // Adjust the speed of the spin
        }
    }
    // Check if the car will be within the track boundaries before updating its position
    if (isOnTrack(newX, newY)) {
        // Reset speed to maxSpeed when on track
        // Update speed
        if (Up && speed < maxSpeed)
            speed += (speed < 0) ? deceleration : acc;
        if (Down && speed > -maxSpeed)
            speed -= (speed > 0) ? deceleration : acc;
        if (!Up && !Down)
            speed += (speed > 0) ? -deceleration : (speed < 0) ? deceleration : 0;

        // Update angle
        if (Right && speed != 0)
            angle += turnSpeed * speed / maxSpeed;
        if (Left && speed != 0)
            angle -= turnSpeed * speed / maxSpeed;

        cars[0].speed = speed;
        cars[0].angle = angle;
        isOutOfBounds = false; // Car is on track, so reset this flag
    } else {
        if (!isOutOfBounds) {
            // Restart the clock when the car first goes out of bounds
            outOfBoundsClock.restart();
        }
        isOutOfBounds = true; // Mark the car as out of bounds

        // Apply deceleration after 0.1 seconds if out of bounds
        if (outOfBoundsClock.getElapsedTime().asSeconds() >= 0.1f) {
            if (speed > 0) 
                speed -= 0.2f;  // Decelerate the car when moving forward
            else if (speed < 0) 
                speed += 0.2f;  // Decelerate the car when moving backward
        }

        // Apply slight acceleration/deceleration when keys are pressed
        if (Up && speed < 5.0f)
            speed += (speed < 0) ? deceleration : 0.3f;
        if (Down && speed > -5.0f)
            speed -= (speed > 0) ? deceleration : 0.3f;
        if (!Up && !Down)
            speed += (speed > 0) ? -deceleration : (speed < 0) ? deceleration : 0;

        // Update angle
        if (Right && speed != 0)
            angle += turnSpeed * speed / maxSpeed;
        if (Left && speed != 0)
            angle -= turnSpeed * speed / maxSpeed;

        cars[0].speed = speed;
        cars[0].angle = angle;
    }

    // Move the player's car with boundary checks
    cars[0].moveWithBoundaries();

    // Update AI cars (move and follow their target)
    for (size_t i = 1; i < cars.size(); ++i) {
        cars[i].move();  // Move AI cars without boundary checks
        cars[i].findTarget();  // Make AI cars follow their waypoints
    }
}


void Game::checkCollisions() {
    for (size_t i = 0; i < cars.size(); ++i) {
        for (size_t j = 0; j < cars.size(); ++j) {
            if (i == j) continue;

            int dx = 0, dy = 0;
            while (dx * dx + dy * dy < 4 * R * R) {
                cars[i].x += dx / 10.0f;
                cars[i].y += dy / 10.0f;
                cars[j].x -= dx / 10.0f;
                cars[j].y -= dy / 10.0f;
                dx = cars[i].x - cars[j].x;
                dy = cars[i].y - cars[j].y;
                if (!dx && !dy) break;
            }
        }
    }
}

void Game::render() {
    // Adjust offsets to stay within map boundaries
    if (cars[0].x > 320) 
        offsetX = std::min(cars[0].x - 320.0f, static_cast<float>(MAP_MAX_X - gameWindow.getSize().x));
    if (cars[0].y > 240) 
        offsetY = std::min(cars[0].y - 240.0f, static_cast<float>(MAP_MAX_Y - gameWindow.getSize().y));

    gameWindow.clear(sf::Color::White);

    // Set the background position with adjusted offset
    sBackground.setPosition(-offsetX, -offsetY);
    gameWindow.draw(sBackground);
    

    // Draw cars
    sf::Color colors[5] = {sf::Color::Red, sf::Color::Green, sf::Color::Magenta, sf::Color::Blue, sf::Color::White};
    for (size_t i = 0; i < cars.size(); ++i) {
        sCar.setPosition(cars[i].x - offsetX, cars[i].y - offsetY);
        sCar.setRotation(cars[i].angle * 180 / M_PI);
        sCar.setColor(colors[i]);
        gameWindow.draw(sCar);
    }
    // Draw boost slider and icon
    gameWindow.draw(boostSlider);
    gameWindow.draw(boostIcon);
    // Draw "Out of Bound" message if applicable
    if (isOutOfBounds) {
        gameWindow.draw(outOfBoundText);
    }
    gameWindow.draw(coordinatesText); // Draw the text in the game window
    gameWindow.display();

}

void Game::activateBoost() {
    if (boostAvailable) {
        isBoosting = true;
        boostAvailable = false;

        speed *= boostMultiplier;

        boostClock.restart();
        cooldownClock.restart();

        SoundManager::playSound("sounds/boost_sound.ogg");
    }
}

void Game::deactivateBoost() {
    if (isBoosting) {
        // Scale the speed back down to normal limits
        speed /= boostMultiplier;

        // Ensure the speed stays within the normal max speed limits
        if (speed > maxSpeed) speed = maxSpeed;
        if (speed < -maxSpeed) speed = -maxSpeed;

        isBoosting = false;
    }
}

void Game::updateBoostVisuals() {
    if (isBoosting) {
        // Update the slider based on remaining boost duration
        float remainingTime = boostDuration - boostClock.getElapsedTime().asSeconds();
        if (remainingTime <= 0) {
            deactivateBoost();
        } else {
            boostSlider.setSize(sf::Vector2f(remainingTime / boostDuration * 100, 10));
        }
    } else if (!boostAvailable) {
        // Update slider for cooldown
        float elapsedTime = cooldownClock.getElapsedTime().asSeconds();
        if (elapsedTime >= boostCooldown) {
            boostAvailable = true;
        } else {
            boostSlider.setSize(sf::Vector2f(elapsedTime / boostCooldown * 100, 10));
        }
        boostSlider.setFillColor(sf::Color::Red);
    } else {
        boostSlider.setFillColor(sf::Color::Green);
        boostSlider.setSize(sf::Vector2f(100, 10));
    }

    // Update icon color based on availability
    boostIcon.setColor(boostAvailable ? sf::Color::White : sf::Color(128, 128, 128));
}