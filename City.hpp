/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef CITY_HPP
#define CITY_HPP

#include "Building.hpp" // Include Building.hpp for Building class and BuildingType enum
#include "Player.hpp"   // Include Player.hpp for Player class
#include "Board.hpp"    // Include Board.hpp for Board class and method declarations

// Forward declaration of Building class to avoid circular inclusion
class Building;

// City class, inherits from Building
class City : public Building {
public:
    // Constructor to initialize a City with its owner and vertex index
    City(Player* owner, int vertex);

    // Destructor to clean up resources when a City is destroyed
    virtual ~City() override;

    // Getter method to retrieve the vertex index of the City
    const int getVertex() const;

    // Method to upgrade a settlement to a city
    // Returns true if the upgrade was successful, false otherwise
    bool upgradeToCity(Player* player, int numVertex, Board& board);
};

#endif // CITY_HPP
