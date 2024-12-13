#include "Car.hpp"
#include <iostream>
// Initialize the target points (checkpoints for the bots) on the track
int Car::points[Car::num][2] = {
    {300, 610},
    {1270, 430},
    {1380, 2380},
    {1900, 2460},
    {1970, 1700},
    {2550, 1680},
    {2560, 3150},
    {500, 3300}
};
int Car::points2[Car::num2][2] = {
    {400, 1047},
    {518, 507},
    {1740, 480},
    {3210, 480},
    {3540, 780},
    {3546, 2290},
    {3085, 2760},
    {500, 2760},
    {500, 1410},
};
Car::Car(float minX, float maxX, float minY, float maxY)
    : minX(minX), maxX(maxX), minY(minY), maxY(maxY) {
    // Initialize other attributes (x, y, speed, etc.)
    x = 0.0f;  // Default values
    y = 0.0f;
    speed = 2.0f;
    angle = 0.0f;
}

// Move the Bot's car based on its current angle and speed
void Car::move() {
    // Calculate new position
    float newX = x + std::sin(angle) * speed;
    float newY = y - std::cos(angle) * speed;

    x = newX; // Update x position only if within bounds

    y = newY; // Update y position only if within bounds
}
void Car::moveWithBoundaries() {
    // Calculate new position based on speed and angle
    float newX = x + std::sin(angle) * speed;
    float newY = y - std::cos(angle) * speed;

    // Apply boundaries to prevent moving outside the map
    if (newX >= minX && newX <= maxX) {
        x = newX; // Update x position only if within bounds
    }
    if (newY >= minY && newY <= maxY) {
        y = newY; // Update y position only if within bounds
    }
}

// Find the next target point and adjust the car's (bots) angle
void Car::findTarget() {
    float tx = points[n][0];  // Target x position
    float ty = points[n][1];  // Target y position
    
    // Calculate the angle difference between current direction and target
    float beta = angle - std::atan2(tx - x, -ty + y);
    
    // Adjust the angle to move towards the target
    if (std::sin(beta) < 0) {
        angle += 0.005 * speed;  // Turn right
    } else {
        angle -= 0.005 * speed;  // Turn left
    }
    
    // Check if the car has reached the target point (within a radius of 25)
    if ((x - tx) * (x - tx) + (y - ty) * (y - ty) < 25 * 25) {
        n = (n + 1) % num;  // Move to the next target (looping back to the start)
    }
}
// Find the next target point and adjust the car's (bots) angle
void Car::findTarget2() {
    float tx = points2[n][0];  // Target x position
    float ty = points2[n][1];  // Target y position
    
    // Calculate the angle difference between current direction and target
    float beta = angle - std::atan2(tx - x, -ty + y);
    
    // Adjust the angle to move towards the target
    if (std::sin(beta) < 0) {
        angle += 0.005 * speed;  // Turn right
    } else {
        angle -= 0.005 * speed;  // Turn left
    }
    
    // Check if the car has reached the target point (within a radius of 25)
    if ((x - tx) * (x - tx) + (y - ty) * (y - ty) < 25 * 25) {
        n = (n + 1) % num;  // Move to the next target (looping back to the start)
    }
}