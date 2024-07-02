#include "Settlement.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Vertex.hpp"
#include "Road.hpp" 
#include "Path.hpp" 


Settlement::Settlement(Player* owner, int vertex)
    : Building(BuildingType::SETTLEMENT, owner, vertex) {}

Settlement::~Settlement() {
    std::cout << "Settlement at vertex " << vertexInd << " destroyed." << std::endl;
}

int Settlement::getVertex() const {
    return vertexInd;
}

bool Settlement::buildSettlement(Player* player, int numVertex, Board& board) {
    if (player == nullptr) {
        std::cout << "The player is invalid" << std::endl;
        return false;
    }

    const Vertex& vertex = board.getVertexFromIndex(numVertex);

    if (vertex.getBuilding() != nullptr){
        if (vertex.getBuilding()->getBuildingTypeName() == "Settlement"){
            std::cout << "Vertex already has a Settlement." << std::endl;
            return false;
        }
    }

    if (vertex.getNumIndex() == -1) {
        std::cout << "Vertex does not exist." << std::endl;
        return false;
    }

    if (vertex.hasAdjacentSettlement(board)) {
        std::cout << "Settlements need a space of two vertices between them." << std::endl;
        return false;
    }

    if (player->getVictoryPoints()>=2){
        
    // Check if the player has a road adjacent to the vertex
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

    type = SETTLEMENT;
    owner = player;
    vertexInd = numVertex;

    board.putPieceOnTheBoard(this, numVertex, -1);

    return true;
}


std::vector<Path*> Settlement::getConnectedRoads(const Board& board) const {
    std::vector<Path*> connectedRoads;

    // Get source and target vertices
    int sourceVertex = getVertex();

    // Iterate over all paths on the board
    for (const Path& path : board.getPaths()) {
        // Check if the path is a road (assume a condition to identify roads)
        if (path.hasRoad()) {  // Adjust this condition based on your implementation
            Road* road = static_cast<Road*>(path.getBuilding()); // Assuming path.getBuilding() returns Building*
            if (road) {
                // Check if the road connects to either source or target vertex of the current road
                if (road->getVertex() == sourceVertex || road->getTarget() == sourceVertex) {
                        connectedRoads.push_back(const_cast<Path*>(&path));
                }
            }
        }
    }

    return connectedRoads;
}
