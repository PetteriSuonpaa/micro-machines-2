#include "Car.hpp"

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


// Constructor to initialize the car's position, speed, and angle
Car::Car() : x(0), y(0), speed(2), angle(0), n(0) {}

// Move the Player's car based on its current angle and speed
void Car::move() {
    // Calculate new position
    float newX = x + std::sin(angle) * speed;
    float newY = y - std::cos(angle) * speed;

    // Apply boundaries to prevent moving outside the map
    if (newX >= MAP_MIN_X && newX <= MAP_MAX_X) {
        x = newX; // Update x position only if within bounds
    }
    if (newY >= MAP_MIN_Y && newY <= MAP_MAX_Y) {
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
