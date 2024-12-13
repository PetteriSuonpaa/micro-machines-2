#ifndef CAR_HPP
#define CAR_HPP

#include <cmath>
#include "mapBoudaries.hpp"

class Car {
public:
    // Static variables
    static const int num = 8; // Number of target points
    static const int num2 = 9; // Number of target points
    static int points[num][2]; // Target points on the map1
    static int points2[num2][2]; // Target points on the map1
    
    // Member variables
    float x, y, speed, angle;  // Car's position, speed, and direction
    float minX, maxX, minY, maxY;  // Boundaries for the car's movement
    int n; // Target point index
 
    
    // Member functions
    void move();
    Car(float minX, float maxX, float minY, float maxY);  // Constructor to set boundaries
    void moveWithBoundaries(); //for the player
    void findTarget();
    void findTarget2();
};

#endif // CAR_HPP
