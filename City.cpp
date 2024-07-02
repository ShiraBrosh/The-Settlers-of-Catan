#include "City.hpp"
#include "Player.hpp"


City::City(Player* owner, int vertex)
    : Building(BuildingType::CITY, owner, vertex) {}

City::~City() {
    std::cout << "City at vertex " << vertexInd << " destroyed." << std::endl;
}   

bool City::upgradeToCity(Player* player, int numVertex, Board& board) {
    if (player == nullptr) {
        std::cout << "The player is invalid" << std::endl;
        return false;
    }

    const Vertex& vertex = board.getVertexFromIndex(numVertex);
    if (vertex.getBuilding() == nullptr || vertex.getBuilding()->getType() != SETTLEMENT) {
        std::cout << "No settlement exists at this vertex to upgrade." << std::endl;
        return false;
    }
    
    // הסרת היישוב הישן
    Building* oldSettlement = vertex.getBuilding();
    player->removeBuilding(oldSettlement);
    
    // עדכון העיר
    type = CITY;
    owner = player;
    vertexInd = numVertex;
    
    // עדכון הלוח
    board.putPieceOnTheBoard(this, numVertex, -1);
    
    return true;
}