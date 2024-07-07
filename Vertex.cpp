/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "Vertex.hpp"
#include <iostream>
#include <algorithm>

// Default constructor
Vertex::Vertex() : numIndex(-1), building(nullptr) {}

// Constructor that initializes the vertex with tiles, paths, and index
Vertex::Vertex(const std::vector<Tile>& tiles, const std::vector<Path>& pathes, int index) 
    : numIndex(index), building(nullptr), tileList(tiles), pathsList(pathes) {
}

// Destructor
Vertex::~Vertex() {}

// Getter for vertex index
int Vertex::getNumIndex() const {
    return numIndex;
}

// Getter for the building on this vertex
Building* Vertex::getBuilding() const {
    return building;
}

// Getter for the paths connected to this vertex
const std::vector<Path>& Vertex::getPaths() const {
    return pathsList;
}

// Return paths that have roads
std::vector<Path> Vertex::getPathsForRoads() const {
    std::vector<Path> pathsWithRoads;
    for (const Path& path : pathsList) {
        if (path.hasRoad()) {
            pathsWithRoads.push_back(path);
        }
    }
    return pathsWithRoads;
}

// Getter for the neighbors of this vertex
const std::vector<int>& Vertex::getNeighbors() const {
    return neighborsList;
}

// Setter for the building on this vertex
void Vertex::setBuilding(Building* newBuilding) {
    if (building != nullptr) {
        // Remove the building from the player's list of buildings
        Player* owner = building->getOwner();
        if (owner != nullptr) {
            auto& playerBuildings = owner->getBuildings();
            auto it = std::find(playerBuildings.begin(), playerBuildings.end(), building);
            if (it != playerBuildings.end()) {
                playerBuildings.erase(it);
                owner->printBuildings(); // Assuming a method to print buildings owned by the player
            }
        }
        delete building; // Assuming ownership management here
    }
    building = newBuilding;
}

// Check if there is a building on this vertex
bool Vertex::hasBuilding() const {
    return building != nullptr && !building->isEmpty();
}

// Check if there is a settlement on this vertex
bool Vertex::hasSettlement() const {
    if (this->hasBuilding() && building->getType() == SETTLEMENT) {
        return true;
    }
    return false;
}

// Check if there is a city on this vertex
bool Vertex::hasCity() const {
    if (this->hasBuilding() && building->getType() == CITY) {
        return true;
    }
    return false;
}

// Check if there is an adjacent settlement to this vertex
bool Vertex::hasAdjacentSettlement(const Board& board) const {
    for (const int& neighborIndex : neighborsList) {
        if (neighborIndex != -1) {
            const Vertex& neighbor = board.getVertexFromIndex(neighborIndex);
            if (neighbor.hasSettlement()) {
                return true;
            }
        }
    }
    return false;
}

// Check if this vertex is adjacent to a given tile
bool Vertex::isAdjacentToTile(Tile tile) const {
    for (const Tile& vertexTile : tileList) {
        if (vertexTile.getResource() == tile.getResource() && vertexTile.getNumber() == tile.getNumber()) {
            return true;
        }
    }
    return false;
}

// Add a neighbor to this vertex if it doesn't already exist in the neighbors list
void Vertex::addNeighbor(int numVertex) {
    // Check if the neighbor is already in the list
    if (std::find(neighborsList.begin(), neighborsList.end(), numVertex) == neighborsList.end()) {
        neighborsList.push_back(numVertex);
    }
}

