#ifndef CAR_HPP
#define CAR_HPP

#include <cmath>
#include "mapBoudaries.hpp"

class Car {
public:
    // Static variables
    static const int num = 8; // Number of target points
    static int points[num][2]; // Target points on the track
    
    // Member variables
    float x, y, speed, angle;  // Car's position, speed, and direction
    int n; // Target point index

    // Constructor
    Car();
    
    // Member functions
    void move();
    void findTarget();
};

#endif // CAR_HPP
