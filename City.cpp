/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "City.hpp"
#include "Player.hpp"
#include <iostream>
#include <algorithm>

// Constructor for City class, initializes a City with its owner and vertex index
City::City(Player* owner, int vertex)
    : Building(BuildingType::CITY, owner, vertex) {}

// Destructor for City class, prints a message when a City is destroyed
City::~City() {
    std::cout << "City at vertex " << vertexInd << " destroyed." << std::endl;
}   

// Function to upgrade a settlement to a city
// Returns true if the upgrade was successful, false otherwise
bool City::upgradeToCity(Player* player, int numVertex, Board& board) {
    // Check if the player is valid
    if (player == nullptr) {
        std::cout << "The player is invalid" << std::endl;
        return false;
    }

    // Get the vertex from the board using the vertex index
    const Vertex& vertex = board.getVertexFromIndex(numVertex);

    // Check if there is an existing building at the vertex and if it's a settlement
    Building* existingBuilding = vertex.getBuilding();
    if (existingBuilding == nullptr || existingBuilding->getType() != SETTLEMENT) {
        std::cout << "No settlement exists at this vertex to upgrade." << std::endl;
        return false;
    }
    
    // Set the city type, owner, and vertex index for this City object
    type = CITY;
    owner = player;
    vertexInd = numVertex;

    // Update the board by placing this City on the board
    board.putPieceOnTheBoard(this, numVertex, -1);
    
    return true;
}
