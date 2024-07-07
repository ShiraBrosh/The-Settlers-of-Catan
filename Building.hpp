/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <iostream>

class Player;

// Enumeration to define different types of buildings
enum BuildingType { NONE, SETTLEMENT, CITY, ROAD };

// Building class to represent different types of buildings on the game board
class Building {
protected:
    BuildingType type;  // Type of the building (SETTLEMENT, CITY, ROAD)
    Player* owner;      // Pointer to the player who owns the building
    int vertexInd;      // Index of the vertex where the building is located

public:
    // Constructor to initialize a Building with its type, owner, and vertex index
    Building(BuildingType type, Player* owner, int vertex);

    // Virtual destructor to clean up resources
    virtual ~Building();

    // Getter function to return the type of the building
    BuildingType getType() const;

    // Getter function to return the owner of the building
    Player* getOwner() const;

    // Getter function to return the owner's name
    std::string getOwnerName() const;

    // Getter function to return the vertex index where the building is located
    const int getVertex() const;

    // Function to check if the building is empty (type is NONE)
    bool isEmpty() const;

    // Function to return the name of the building type as a string
    std::string getBuildingTypeName() const;
};

#endif // BUILDING_HPP
