#include "Game.hpp"

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
        car.speed = 7 + i;
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

        handleCarMovement();
        updateBoostVisuals();
        checkCollisions();
        render();
    }
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

    for (auto& car : cars) car.move();
    for (size_t i = 1; i < cars.size(); ++i) cars[i].findTarget();
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
    gameWindow.clear(sf::Color::White);

    // Adjust camera offset
    if (cars[0].x > 320) offsetX = cars[0].x - 320;
    if (cars[0].y > 240) offsetY = cars[0].y - 240;

    // Draw background
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