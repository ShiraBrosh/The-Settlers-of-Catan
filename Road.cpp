/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "Road.hpp"       
#include "Player.hpp"     
#include "Board.hpp"      
#include "Vertex.hpp"     
#include <iostream>      

// Constructor: initializes a road with its owner, source vertex, and target vertex
Road::Road(Player* owner, int source, int target)
    : Building(BuildingType::ROAD, owner, source), target(target) {}

// Destructor: prints a message when a road object is destroyed
Road::~Road() {
    std::cout << "Road from vertex " << vertexInd << " to " << target << " destroyed." << std::endl;
}

// Getter function to retrieve the target vertex of the road
int Road::getTarget() const {
    return target;
}

// Function to attempt to build a road between two vertices on the board
bool Road::buildRoad(Player* player, int numSource, int numTarget, Board& board) {
    // Check if the player is valid
    if (player == nullptr) {
        std::cout << "The player is invalid" << std::endl;
        return false;
    }

    // Check if the vertices are within valid range on the board
    if (numSource < 0 || numSource >= board.getNumVertices() || numTarget < 0 || numTarget >= board.getNumVertices()) {
        std::cout << "The number of vertices is out of range" << std::endl;
        return false;
    }

    // Get the path between the specified source and target vertices
    const Path& path = board.getPathFromIndexes(numSource, numTarget);

    // Check if the path already has a building or road
    if (path.getBuilding() != nullptr || path.hasRoad()) {
        std::cout << "Path is invalid or already has a building." << std::endl;
        return false;
    }

    // Check if there is already a road on this edge
    if (board.hasRoadOnEdge(numSource, numTarget)) {
        std::cout << "There is already a road on this edge." << std::endl;
        return false;
    }

    // Attempt to connect the road to the player's settlement, city, or existing road
    if (connectOwnerBuild(player, numSource, numTarget, board)) {
        type = ROAD;                          // Set the type of the building to ROAD
        owner = player;                       // Set the owner of the road
        vertexInd = numSource;                // Set the source vertex index of the road
        target = numTarget;                   // Set the target vertex index of the road
        board.putPieceOnTheBoard(this, numSource, numTarget); // Place the road on the board
        return true;
    } else {
        return false;
    }
}

// Helper function to check if the player can connect a road to their own settlement, city, or road
bool Road::connectOwnerBuild(Player* player, int numSource, int numTarget, Board& board) {
    // Check if either the source or target vertex has a settlement or city owned by the player
    if ((board.getVertexFromIndex(numSource).hasBuilding() && board.getVertexFromIndex(numSource).getBuilding()->getOwner() == player &&
         (board.getVertexFromIndex(numSource).getBuilding()->getType() == SETTLEMENT || board.getVertexFromIndex(numSource).getBuilding()->getType() == CITY)) ||
        (board.getVertexFromIndex(numTarget).hasBuilding() && board.getVertexFromIndex(numTarget).getBuilding()->getOwner() == player &&
         (board.getVertexFromIndex(numTarget).getBuilding()->getType() == SETTLEMENT || board.getVertexFromIndex(numTarget).getBuilding()->getType() == CITY))) {
            return true;
    }

    // Check if there are connected roads owned by the player
    std::vector<Path*> connectedRoads = getConnectedRoads(board);
    for (int i = 0; i < connectedRoads.size(); i++) {
        if (connectedRoads[i]->hasRoad() && connectedRoads[i]->getBuilding()->getOwnerName() == player->getName()) {
            return true;
        }
    }

    // If none of the conditions are met, output an error message and return false
    std::cout << "You can only build a road connected to your own road, settlement, or city." << std::endl;
    return false;
}

// Function to retrieve a vector of paths that are connected to this road on the board
std::vector<Path*> Road::getConnectedRoads(const Board& board) const {
    std::vector<Path*> connectedRoads;

    // Get the source and target vertices of the road
    int sourceVertex = getVertex();
    int targetVertex = target;

    // Helper lambda function to add connected roads to the vector
    auto addConnectedRoads = [&](int vertex) {
        for (const Path& path : board.getPaths()) {
            if (path.hasRoad()) {
                Road* road = static_cast<Road*>(path.getBuilding());
                if (road) {
                    if (road->getVertex() == vertex || road->getTarget() == vertex) {
                        connectedRoads.push_back(const_cast<Path*>(&path));
                    }
                }
            }
        }
    };

    // Add connected roads for both source and target vertices
    addConnectedRoads(sourceVertex);
    addConnectedRoads(targetVertex);

    return connectedRoads;
}
