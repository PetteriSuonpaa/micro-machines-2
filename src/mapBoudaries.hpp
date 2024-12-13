#ifndef MAPBOUNDARIES_HPP
#define MAPBOUNDARIES_HPP
#include <SFML/Graphics.hpp>  // To use sf::FloatRect
#include <vector>              // For std::vector

// Define the boundaries of the map (of the fist map)
const int MAP_MIN_X = 0;       // Minimum x boundary
const int MAP_MAX_X = 2850;    // Maximum x boundary
const int MAP_MIN_Y = 0;       // Minimum y boundary
const int MAP_MAX_Y = 3620;    // Maximum y boundary

// Define the boundaries of the map (of the second map)
const int MAP_MIN_X2 = 0;       // Minimum x boundary
const int MAP_MAX_X2 = 4000;    // Maximum x boundary
const int MAP_MIN_Y2 = 0;       // Minimum y boundary
const int MAP_MAX_Y2 = 3040;    // Maximum y boundary

extern std::vector<sf::FloatRect> trackBounds;
extern std::vector<sf::FloatRect> trackBounds2;
extern std::vector<sf::FloatRect> oilSpillBounds;



#endif // MAPBOUNDARIES_HPP