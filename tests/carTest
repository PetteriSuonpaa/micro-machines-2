#include <gtest/gtest.h>
#include "Car.hpp"
#include "Car.cpp"
#include <cmath>

// Constants to help with float comparisons
const float EPSILON = 0.01f;

// Test constructor initialization
TEST(CarTests, Initialization) {
    Car car;

    // Ensure initial values are correct
    EXPECT_FLOAT_EQ(car.getX(), 0);
    EXPECT_FLOAT_EQ(car.getY(), 0);
    EXPECT_FLOAT_EQ(car.getSpeed(), 2);
    EXPECT_FLOAT_EQ(car.getAngle(), 0);
    EXPECT_EQ(car.getCurrentTargetIndex(), 0);
}

// Test the car's movement functionality
TEST(CarTests, Movement) {
    Car car;
    car.setPosition(0, 0);  // Start at (0, 0)
    car.setSpeed(5);        // Set a speed

    // Move the car forward and validate the new position
    car.setAngle(0);        // Moving straight up (y decreases)
    car.move();
    EXPECT_NEAR(car.getX(), 0, EPSILON);
    EXPECT_NEAR(car.getY(), -5, EPSILON);

    car.setAngle(M_PI / 2); // Moving to the right (x increases)
    car.move();
    EXPECT_NEAR(car.getX(), 5, EPSILON);
    EXPECT_NEAR(car.getY(), -5, EPSILON);
}

// Test target finding and angle adjustments
TEST(CarTests, FindTarget) {
    Car car;
    car.setPosition(300, 600);  // Start near the first target (300, 610)
    car.setSpeed(1);

    // Simulate target tracking
    car.findTarget();
    EXPECT_NEAR(car.getAngle(), 0.0f, EPSILON);  // Initially pointing straight up

    car.move();  // Move closer to the first target
    EXPECT_EQ(car.getCurrentTargetIndex(), 0);  // Still targeting the first point

    car.setPosition(300, 610);  // Position exactly on the target
    car.findTarget();
    EXPECT_EQ(car.getCurrentTargetIndex(), 1);  // Should now target the second point
}

// Test looping through all target points
TEST(CarTests, TargetLooping) {
    Car car;
    car.setSpeed(1);

    // Move through all target points
    for (int i = 0; i < Car::num; ++i) {
        car.setPosition(Car::points[i][0], Car::points[i][1]);  // Place car at the current target
        car.findTarget();
        EXPECT_EQ(car.getCurrentTargetIndex(), (i + 1) % Car::num);  // Next target index
    }
}

// Test reaching a target
TEST(CarTests, ReachingTarget) {
    Car car;
    car.setSpeed(1);
    car.setPosition(300, 610);  // At the first target

    car.findTarget();
    EXPECT_EQ(car.getCurrentTargetIndex(), 1);  // Should now target the second point
}

// Test angle adjustment for a right turn
TEST(CarTests, AngleAdjustmentRightTurn) {
    Car car;
    car.setPosition(300, 610);
    car.setAngle(-M_PI / 2);  // Facing left, needs to adjust to target (1270, 430)
    car.setSpeed(1);

    car.findTarget();

    // The car should turn right
    EXPECT_GT(car.getAngle(), -M_PI / 2);
}

// Test angle adjustment for a left turn
TEST(CarTests, AngleAdjustmentLeftTurn) {
    Car car;
    car.setPosition(300, 610);
    car.setAngle(M_PI / 2);  // Facing right, needs to adjust to target (1270, 430)
    car.setSpeed(1);

    car.findTarget();

    // The car should turn left
    EXPECT_LT(car.getAngle(), M_PI / 2);
}
