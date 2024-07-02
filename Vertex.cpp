#include "Vertex.hpp"

Vertex::Vertex() : numIndex(0), building(nullptr) {}

Vertex::Vertex(const std::vector<Tile>& tiles, const std::vector<Path>& pathes, int index): 
    numIndex(index), building(nullptr), tileList(tiles), pathsList(pathes) {}

Vertex::~Vertex() {
    delete building;
}

int Vertex::getNumIndex() const {
    return numIndex;
}

Building* Vertex::getBuilding() const {
    return building;
}


const std::vector<Path>& Vertex::getPaths() const {
    return pathsList;
}


std::vector<Path> Vertex::getPathsForRoads() const {
    std::vector<Path> pathsWithBuilding;
    for (const Path& path : pathsList) {
        if (path.hasRoad()) {
            pathsWithBuilding.push_back(path);
        }
    }
    return pathsWithBuilding;
}

const std::vector<int>& Vertex::getNeighbors() const {
        return neighborsList;
    }

void Vertex::setBuilding(Building* newBuilding) {
    if (building != nullptr) {
        delete building;
    }
    building = newBuilding;
}

bool Vertex::hasBuilding() const {
    return building != nullptr && !building->isEmpty();
}



bool Vertex::hasSettlement() const {
    if (this->hasBuilding() && building->getType() == SETTLEMENT) {
            return true;
    }
    return false;
}

bool Vertex::hasCity() const {
    if (this->hasBuilding() && building->getType() == CITY) {
            return true;
    }
    return false;
}


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



bool Vertex::isAdjacentToTile(Tile tile) const {
    for (int i=0; i<tileList.size(); i++){
        if(tileList[i].getResource() == tile.getResource() && tileList[i].getNumber() == tile.getNumber())
            return true;
    }

    return false;
}


void Vertex::addNeighbor(int numVertex){
     // Check if the neighbor is already in the list
    for (int neighbor : neighborsList) {
        if (neighbor == numVertex) {
            return; // Neighbor already exists, no need to add
        }
    }
    // Add the new neighbor
    neighborsList.push_back(numVertex);
}
