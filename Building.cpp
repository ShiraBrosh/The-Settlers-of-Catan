/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "Building.hpp"
#include "Player.hpp"

// Constructor to initialize a Building with its type, owner, and vertex index
Building::Building(BuildingType type, Player* owner, int vertex)
    : type(type), owner(owner), vertexInd(vertex) {}

// Destructor to clean up resources
Building::~Building() {
    type = NONE; // Reset type to NONE
    owner = nullptr; // Set owner pointer to nullptr
    vertexInd = 0; // Reset vertex index to 0
}

// Getter function to return the type of the building
BuildingType Building::getType() const {
    return type;
}

// Getter function to return the owner of the building
Player* Building::getOwner() const {
    return owner;
}

// Getter function to return the owner's name
std::string Building::getOwnerName() const {
    if (owner != nullptr) {
        return owner->getName(); // Return the owner's name if owner is not null
    } else {
        std::cerr << "Error: Building owner is null!" << std::endl; // Print error if owner is null
        return "Unknown"; // Return "Unknown" if owner is null
    }
}

// Getter function to return the vertex index where the building is located
const int Building::getVertex() const {
    return vertexInd;
}    

// Function to check if the building is empty (type is NONE)
bool Building::isEmpty() const {
    return (type == NONE);
}

// Function to return the name of the building type as a string
std::string Building::getBuildingTypeName() const {
    switch (type) {
        case SETTLEMENT:
            return "Settlement"; // Return "Settlement" if type is SETTLEMENT
        case CITY:
            return "City"; // Return "City" if type is CITY
        case ROAD:
            return "Road"; // Return "Road" if type is ROAD
        default:
            return "Unknown"; // Return "Unknown" for any other type
    }
}
