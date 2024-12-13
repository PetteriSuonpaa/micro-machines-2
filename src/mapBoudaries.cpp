#include "mapBoudaries.hpp"

// Define the track boundaries (only once)
std::vector<sf::FloatRect> trackBounds = {   //{x, y, width, height}
    {214, 602, 210, 2543}, // Updated first track region
    {214, 345, 426, 257}, // Second track region
    {640, 345, 540, 257}, // third track region
    {1180, 345, 320, 257}, // forth track region
    {1271, 602, 229, 1843}, // fitht track region
    {1271, 2445, 300, 260}, // sixth track region
    {1530, 2496, 300, 217}, // seventh track region
    {1831, 1683, 170, 1006}, // eight track region
    {1820, 1524, 836 ,160 }, // ninth track region
    {2477, 1683, 191, 1261}, // tenth track region
    {2444, 2944, 191, 252}, // eleventh track region
    {2214, 2944, 230, 252}, //  12track region
    {2248, 3196, 230, 213}, // 13 track region
    {469, 3196, 1779, 244}, // 14 track region
    {214, 3145, 255, 295}, // 15 track region
};


std::vector<sf::FloatRect> oilSpillBounds = { // {x, y, width, height}
    {340, 1548, 36, 30},   // Oil spill 1
    {466, 416, 25, 25},   // Oil spill 2
    {655, 396, 40, 40},  // Oil spill 3
    {2007, 1620, 30, 30}, // Oil spill 4
    {2557, 2436, 32, 32},  // Oil spill 5
    {793, 3278, 50, 50},  // Oil spill 6 and 7
    {263, 3148, 40, 40},  // Oil spill 8
    {350, 2453, 33, 33},  // Oil spill 9
};

