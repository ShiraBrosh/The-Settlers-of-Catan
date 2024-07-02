#include "Road.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Vertex.hpp"
#include <iostream>

Road::Road(Player* owner, int source, int target)
    : Building(BuildingType::ROAD, owner, source), target(target) {}

Road::~Road() {
    std::cout << "Road from vertex " << vertexInd << " to " << target << " destroyed." << std::endl;
} 

int Road::getTarget() const {
    return target;
}
bool Road::buildRoad(Player* player, int numSource, int numTarget, Board& board) {
    if (player == nullptr) {
        std::cout << "The player is invalid" << std::endl;
        return false;
    }

    if (numSource < 0 || numSource >= board.getNumVertices() || numTarget < 0 || numTarget >= board.getNumVertices()) {
        std::cout << "The number of vertices is out of range" << std::endl;
        return false;
    }

    const Path& path = board.getPathFromIndexes(numSource, numTarget);

    if (path.getBuilding() != nullptr || path.hasRoad()) {
        std::cout << "Path is invalid or already has a building." << std::endl;
        return false;
    }

    // Check if there is already a road on this edge
    if (board.hasRoadOnEdge(numSource, numTarget)) {
        std::cout << "There is already a road on this edge." << std::endl;
        return false;
    }
    
    if (connectOwnerBuild(player, numSource, numTarget, board)){
        type = ROAD;
        owner = player;
        vertexInd = numSource;
        target = numTarget;
        board.putPieceOnTheBoard(this, numSource, numTarget);

        return true;
    } else {
        return false;
    }
}

bool Road::connectOwnerBuild(Player* player, int numSource, int numTarget, Board& board){
    if ((board.getVertexFromIndex(numSource).hasBuilding() && board.getVertexFromIndex(numSource).getBuilding()->getOwner() == player &&
         (board.getVertexFromIndex(numSource).getBuilding()->getType() == SETTLEMENT || board.getVertexFromIndex(numSource).getBuilding()->getType() == CITY)) ||
        (board.getVertexFromIndex(numTarget).hasBuilding() && board.getVertexFromIndex(numTarget).getBuilding()->getOwner() == player &&
         (board.getVertexFromIndex(numTarget).getBuilding()->getType() == SETTLEMENT || board.getVertexFromIndex(numTarget).getBuilding()->getType() == CITY))) {
            return true;
    }

    std::vector<Path*> connectedRoads= getConnectedRoads(board);
    for (int i=0; i<connectedRoads.size(); i++){
        if (connectedRoads[i]->hasRoad() && connectedRoads[i]->getBuilding()->getOwnerName() == player->getName()){
            return true;
        }
    }
    std::cout << "You can only build a road connected to your own road, settlement or city." << std::endl;
    return false;
}

std::vector<Path*> Road::getConnectedRoads(const Board& board) const {
    std::vector<Path*> connectedRoads;

    // Get source and target vertices
    int sourceVertex = getVertex();
    int targetVertex = target;

    // Helper function to add connected roads
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
