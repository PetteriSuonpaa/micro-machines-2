#include "Game.hpp"

Game::Game(float windowWidth, float windowHeight)
    : gameWindow(sf::VideoMode(windowWidth, windowHeight), "Car Racing Game"),
      speed(0), angle(0), offsetX(0), offsetY(0) {
    // Load textures
    bgTexture.loadFromFile("images/background.png");
    carTexture.loadFromFile("images/car.png");

    // Setup sprites
    sBackground.setTexture(bgTexture);
    sBackground.scale(2, 2);
    carTexture.setSmooth(true);
    sCar.setTexture(carTexture);
    sCar.setOrigin(R, R);

    // Initialize cars
    for (int i = 0; i < N; ++i) {
        Car car;
        car.x = 300 + i * 50;
        car.y = 1700 + i * 80;
        car.speed = 7 + i;
        cars.push_back(car);
    }

    gameWindow.setFramerateLimit(60);
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
        checkCollisions();
        render();
    }
}

void Game::handleCarMovement() {
    bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

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

    gameWindow.display();
}
