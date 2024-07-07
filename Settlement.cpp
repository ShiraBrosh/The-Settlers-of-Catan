/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "Settlement.hpp"   
#include "Player.hpp"       
#include "Board.hpp"        
#include "Vertex.hpp"     
#include "Road.hpp"        
#include "Path.hpp"        
#include <iostream>         

Settlement::Settlement(Player* owner, int vertex)
    : Building(BuildingType::SETTLEMENT, owner, vertex) {
    // Constructor: initializes a Settlement with its type and owner
}

Settlement::~Settlement() {
    // Destructor: prints a message when a Settlement is destroyed
    std::cout << "Settlement at vertex " << vertexInd << " destroyed." << std::endl;
}

int Settlement::getVertex() const {
    // Function to retrieve the vertex index where the Settlement is built
    return vertexInd;
}

bool Settlement::buildSettlement(Player* player, int numVertex, Board& board) {
    // Function to build a Settlement for a player on a specified vertex

    // Check if the player is valid
    if (player == nullptr) {
        std::cout << "The player is invalid" << std::endl;
        return false;
    }

    // Get the vertex object from the board using its index
    const Vertex& vertex = board.getVertexFromIndex(numVertex);

    // Check if there is already a building at the vertex
    if (vertex.getBuilding() != nullptr) {
        if (vertex.getBuilding()->getBuildingTypeName() == "Settlement") {
            std::cout << "Vertex already has a Settlement." << std::endl;
            return false;
        }
    }

    // Check if the vertex exists on the board
    if (vertex.getNumIndex() == -1) {
        std::cout << "Vertex does not exist." << std::endl;
        return false;
    }

    // Check adjacency rules for settlements
    if (vertex.hasAdjacentSettlement(board)) {
        std::cout << "Settlements need a space of two vertices between them." << std::endl;
        return false;
    }

    // Check if the player has enough victory points to build a settlement
    if (player->getVictoryPoints() >= 2) {
        // Check if there is an adjacent road owned by the player
        std::vector<Path*> connectedRoads = getConnectedRoads(board);
        bool hasAdjacentRoad = false;
        for (Path* road : connectedRoads) {
            if (road->hasRoad() && road->getBuilding()->getOwnerName() == player->getName()) {
                hasAdjacentRoad = true;
                break;
            }
        }

        if (!hasAdjacentRoad) {
            std::cout << "Cannot build a settlement without an adjacent road." << std::endl;
            return false;
        }
    }

    // If all conditions are met, build the settlement
    type = SETTLEMENT;
    owner = player;
    vertexInd = numVertex;

    board.putPieceOnTheBoard(this, numVertex, -1);

    return true;
}

std::vector<Path*> Settlement::getConnectedRoads(const Board& board) const {
    // Function to retrieve all roads connected to the settlement's vertex on the board
    std::vector<Path*> connectedRoads;

    // Get the source vertex of the settlement
    int sourceVertex = getVertex();

    // Iterate over all paths on the board
    for (const Path& path : board.getPaths()) {
        // Check if the path represents a road (adjust this condition based on your implementation)
        if (path.hasRoad()) {
            Road* road = static_cast<Road*>(path.getBuilding()); // Assuming path.getBuilding() returns Building*
            if (road) {
                // Check if the road connects to either the source vertex or its target
                if (road->getVertex() == sourceVertex || road->getTarget() == sourceVertex) {
                    connectedRoads.push_back(const_cast<Path*>(&path));
                }
            }
        }
    }

    return connectedRoads;
}

