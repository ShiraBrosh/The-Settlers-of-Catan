/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/


#include "Board.hpp"
#include <set> 

#include <iostream>

// Create the standard Catan board with 19 tiles
Board::Board() : tiles{
    {WOOD, 9}, {WOOD, 3}, {WOOD, 11}, {WOOD, 8},
    {BRICK, 6}, {BRICK, 10}, {BRICK, 5},
    {SHEEP, 2}, {SHEEP, 4}, {SHEEP, 5}, {SHEEP, 11},
    {WHEAT, 12}, {WHEAT, 9}, {WHEAT, 4}, {WHEAT, 6},
    {IRON, 10}, {IRON, 3}, {IRON, 8},
    {DESERT, 0} // Desert tile has no number
} {

    for (const Tile& tile : tiles) {
        int number = tile.getNumber();
        if (number != 0) { // Skip the desert tile
            numberTiles[number].push_back(tile);
        }
    }

    initializePaths();
    initializeVertices();
    initializeNeighbors();
}

// Destructor for the Board class
Board::~Board() {
    // Iterate through all vertices to clear buildings
    for (int i = 0; i < vertices.size(); i++) {
        int vertexIndex = vertices[i].getNumIndex();

        // Ensure the vertex index is within a valid range
        if (vertexIndex >= 0 && vertexIndex < static_cast<int>(vertices.size())) {
            Building* building = vertices[i].getBuilding();
            if (building != nullptr) {
                // Clear the building pointer to avoid dangling references
                vertices[i].setBuilding(nullptr);
            }
        }
    }

    // Iterate through all paths to clear buildings
    for (int i = 0; i < pathes.size(); i++) {
        // Check if the path is valid by confirming both source and target vertices
        if (pathes[i].getSource() > 0 && pathes[i].getTarget() > 0) {
            Building* building = pathes[i].getBuilding();
            if (building != nullptr) {
                // Clear the building pointer to avoid dangling references
                pathes[i].setBuilding(nullptr);
            }
        }
    }

    // Clear the vectors to release the memory
    vertices.clear();
    pathes.clear();
}


void Board::initializePaths() {
    // Initialize paths between vertices
   pathes = {
    Path(1, 4), Path(1, 5), Path(2, 5), Path(2, 6), Path(3, 6), Path(3, 7), Path(4, 8), Path(5, 9), Path(6, 10), Path(7, 11),
    Path(8, 12), Path(8, 13), Path(9, 13), Path(9, 14), Path(10, 14), Path(10, 15), Path(11, 15), Path(11, 16), Path(12, 17),
    Path(13, 18), Path(14, 19), Path(15, 20),
    Path(16, 21), Path(17, 22), Path(17, 23), Path(18, 23), Path(18, 24), Path(19, 24), Path(19, 25), Path(20, 25), Path(20, 26), 
    Path(21, 26), Path(21, 27), Path(22, 28), Path(23, 29),
    Path(24, 30), Path(25, 31), Path(26, 32), Path(27, 33), Path(28, 34), Path(29, 34), Path(29, 35), Path(30, 35), Path(30, 36),
    Path(31, 36), Path(31, 37), Path(32, 37), Path(32, 38), Path(33, 38),
    Path(34, 39), Path(35, 40), Path(36, 41), Path(37, 42), Path(38, 43), Path(39, 44), Path(40, 44),Path(40, 45), Path(41, 45),
    Path(41, 46), Path(42, 46), Path(42, 47), Path(43, 47),
    Path(44, 48), Path(45, 49), Path(46, 50), Path(47, 51), Path(48, 52), Path(49, 52), Path(49, 53), Path(50, 53), Path(50, 54), 
    Path(51, 54), Path(-1, -1)
};
}
void Board::initializeVertices() {
    // Initializing vertices with resources and paths
    vertices = {
        Vertex({tiles[15]}, {pathes[0], pathes[1]}, 1), Vertex({tiles[7]}, {pathes[3], pathes[2]}, 2), Vertex({tiles[0]}, {pathes[4], pathes[5]}, 3),
        Vertex({tiles[15]}, {pathes[0], pathes[6]}, 4), Vertex({tiles[15], tiles[7]}, {pathes[1], pathes[2], pathes[7]}, 5), Vertex({tiles[7], tiles[0]}, {pathes[3], pathes[4], pathes[8]}, 6),
        Vertex({tiles[0]}, {pathes[5], pathes[9]}, 7), Vertex({tiles[11], tiles[15]}, {pathes[6], pathes[10], pathes[11]}, 8), Vertex({tiles[15], tiles[7], tiles[4]}, {pathes[7], pathes[12], pathes[13]}, 9),
        Vertex({tiles[7], tiles[0], tiles[8]}, {pathes[8], pathes[14], pathes[15]}, 10), Vertex({tiles[0], tiles[5]}, {pathes[9], pathes[16], pathes[17]}, 11), Vertex({tiles[11]}, {pathes[10], pathes[18]}, 12),
        Vertex({tiles[15], tiles[11], tiles[4]}, {pathes[11], pathes[12], pathes[19]}, 13), Vertex({tiles[7], tiles[4], tiles[8]}, {pathes[13], pathes[14], pathes[20]}, 14), Vertex({tiles[0], tiles[8], tiles[5]}, {pathes[15], pathes[16], pathes[21]}, 15),
        Vertex({tiles[5]}, {pathes[17], pathes[22]}, 16), Vertex({tiles[11], tiles[12]}, {pathes[18], pathes[23], pathes[24]}, 17), Vertex({tiles[11], tiles[4], tiles[2]}, {pathes[19], pathes[25], pathes[26]}, 18),
        Vertex({tiles[4], tiles[8], tiles[18]}, {pathes[20], pathes[27], pathes[28]}, 19), Vertex({tiles[8], tiles[5], tiles[1]}, {pathes[21], pathes[29], pathes[30]}, 20), Vertex({tiles[5], tiles[17]}, {pathes[22], pathes[31], pathes[32]}, 21),
        Vertex({tiles[12]}, {pathes[23], pathes[33]}, 22), Vertex({tiles[11], tiles[12], tiles[2]}, {pathes[24], pathes[25], pathes[34]}, 23), Vertex({tiles[4], tiles[2], tiles[18]}, {pathes[26], pathes[27], pathes[35]}, 24),
        Vertex({tiles[8], tiles[1], tiles[18]}, {pathes[28], pathes[29], pathes[36]}, 25), Vertex({tiles[5], tiles[1], tiles[17]}, {pathes[30], pathes[31], pathes[37]}, 26), Vertex({tiles[17]}, {pathes[32], pathes[38]}, 27),
        Vertex({tiles[12]}, {pathes[33], pathes[39]}, 28), Vertex({tiles[12], tiles[2], tiles[3]}, {pathes[34], pathes[40], pathes[41]}, 29), Vertex({tiles[2], tiles[18], tiles[16]}, {pathes[35], pathes[42], pathes[43]}, 30),
        Vertex({tiles[18], tiles[1], tiles[13]}, {pathes[36], pathes[44], pathes[45]}, 31), Vertex({tiles[1], tiles[17], tiles[9]}, {pathes[37], pathes[46], pathes[47]}, 32), Vertex({tiles[17]}, {pathes[38], pathes[48]}, 33),
        Vertex({tiles[12], tiles[3]}, {pathes[39], pathes[40], pathes[49]}, 34), Vertex({tiles[2], tiles[3], tiles[16]}, {pathes[41], pathes[42], pathes[50]}, 35), Vertex({tiles[18], tiles[16], tiles[13]}, {pathes[43], pathes[44], pathes[51]}, 36),
        Vertex({tiles[1], tiles[13], tiles[9]}, {pathes[45], pathes[46], pathes[52]}, 37), Vertex({tiles[17], tiles[9]}, {pathes[47], pathes[48], pathes[53]}, 38), Vertex({tiles[3]}, {pathes[49], pathes[54]}, 39),
        Vertex({tiles[3], tiles[16], tiles[6]}, {pathes[50], pathes[55], pathes[56]}, 40), Vertex({tiles[16], tiles[13], tiles[14]}, {pathes[51], pathes[57], pathes[58]}, 41), Vertex({tiles[13], tiles[9], tiles[10]}, {pathes[52], pathes[59], pathes[60]}, 42),
        Vertex({tiles[9]}, {pathes[53], pathes[61]}, 43), Vertex({tiles[3], tiles[6]}, {pathes[54], pathes[62], pathes[55]}, 44), Vertex({tiles[14], tiles[16], tiles[6]}, {pathes[56], pathes[57], pathes[63]}, 45),
        Vertex({tiles[13], tiles[14], tiles[10]}, {pathes[58], pathes[59], pathes[64]}, 46), Vertex({tiles[9], tiles[10]}, {pathes[60], pathes[61], pathes[65]}, 47), Vertex({tiles[6]}, {pathes[62], pathes[66]}, 48),
        Vertex({tiles[6], tiles[14]}, {pathes[63], pathes[67], pathes[68]}, 49), Vertex({tiles[14], tiles[10]}, {pathes[64], pathes[69], pathes[70]}, 50), Vertex({tiles[10]}, {pathes[65], pathes[71]}, 51), Vertex({tiles[6]}, {pathes[66], pathes[67]}, 52),
        Vertex({tiles[14]}, {pathes[68], pathes[69]}, 53), Vertex({tiles[10]}, {pathes[70], pathes[71]}, 54), Vertex({}, {}, -1)
    };
}

void Board::initializeNeighbors() {
    vertices[0].addNeighbor(4);
    vertices[0].addNeighbor(5);

    vertices[1].addNeighbor(5);
    vertices[1].addNeighbor(6);

    vertices[2].addNeighbor(6);
    vertices[2].addNeighbor(7);

    vertices[3].addNeighbor(1);
    vertices[3].addNeighbor(8);

    vertices[4].addNeighbor(1);
    vertices[4].addNeighbor(2);
    vertices[4].addNeighbor(9);

    vertices[5].addNeighbor(2);
    vertices[5].addNeighbor(3);
    vertices[5].addNeighbor(10);

    vertices[6].addNeighbor(3);
    vertices[6].addNeighbor(11);

    vertices[7].addNeighbor(4);
    vertices[7].addNeighbor(12);
    vertices[7].addNeighbor(13);

    vertices[8].addNeighbor(5);
    vertices[8].addNeighbor(13);
    vertices[8].addNeighbor(14);

    vertices[9].addNeighbor(6);
    vertices[9].addNeighbor(14);
    vertices[9].addNeighbor(15);

    vertices[10].addNeighbor(7);
    vertices[10].addNeighbor(15);
    vertices[10].addNeighbor(16);

    vertices[11].addNeighbor(8);
    vertices[11].addNeighbor(17);

    vertices[12].addNeighbor(8);
    vertices[12].addNeighbor(9);
    vertices[12].addNeighbor(18);

    vertices[13].addNeighbor(9);
    vertices[13].addNeighbor(10);
    vertices[13].addNeighbor(19);

    vertices[14].addNeighbor(10);
    vertices[14].addNeighbor(11);
    vertices[14].addNeighbor(20);

    vertices[15].addNeighbor(11);
    vertices[15].addNeighbor(21);

    vertices[16].addNeighbor(12);
    vertices[16].addNeighbor(22);
    vertices[16].addNeighbor(23);

    vertices[17].addNeighbor(13);
    vertices[17].addNeighbor(23);
    vertices[17].addNeighbor(24);

    vertices[18].addNeighbor(14);
    vertices[18].addNeighbor(24);
    vertices[18].addNeighbor(25);

    vertices[19].addNeighbor(15);
    vertices[19].addNeighbor(25);
    vertices[19].addNeighbor(26);

    vertices[20].addNeighbor(16);
    vertices[20].addNeighbor(26);
    vertices[20].addNeighbor(27);

    vertices[21].addNeighbor(17);
    vertices[21].addNeighbor(28);

    vertices[22].addNeighbor(17);
    vertices[22].addNeighbor(18);
    vertices[22].addNeighbor(29);

    vertices[23].addNeighbor(18);
    vertices[23].addNeighbor(19);
    vertices[23].addNeighbor(30);

    vertices[24].addNeighbor(19);
    vertices[24].addNeighbor(20);
    vertices[24].addNeighbor(31);

    vertices[25].addNeighbor(20);
    vertices[25].addNeighbor(21);
    vertices[25].addNeighbor(32);

    vertices[26].addNeighbor(21);
    vertices[26].addNeighbor(33);

    vertices[27].addNeighbor(22);
    vertices[27].addNeighbor(34);

    vertices[28].addNeighbor(23);
    vertices[28].addNeighbor(34);
    vertices[28].addNeighbor(35);

    vertices[29].addNeighbor(24);
    vertices[29].addNeighbor(35);
    vertices[29].addNeighbor(36);

    vertices[30].addNeighbor(25);
    vertices[30].addNeighbor(36);
    vertices[30].addNeighbor(37);

    vertices[31].addNeighbor(26);
    vertices[31].addNeighbor(37);
    vertices[31].addNeighbor(38);

    vertices[32].addNeighbor(27);
    vertices[32].addNeighbor(38);

    vertices[33].addNeighbor(28);
    vertices[33].addNeighbor(29);
    vertices[33].addNeighbor(39);

    vertices[34].addNeighbor(30);
    vertices[34].addNeighbor(29);
    vertices[34].addNeighbor(40);

    vertices[35].addNeighbor(31);
    vertices[35].addNeighbor(30);
    vertices[35].addNeighbor(41);

    vertices[36].addNeighbor(32);
    vertices[36].addNeighbor(31);
    vertices[36].addNeighbor(42);

    vertices[37].addNeighbor(33);
    vertices[37].addNeighbor(32);
    vertices[37].addNeighbor(43);

    vertices[38].addNeighbor(34);
    vertices[38].addNeighbor(44);

    vertices[39].addNeighbor(35);
    vertices[39].addNeighbor(45);
    vertices[39].addNeighbor(44);

    vertices[40].addNeighbor(36);
    vertices[40].addNeighbor(45);
    vertices[40].addNeighbor(46);

    vertices[41].addNeighbor(37);
    vertices[41].addNeighbor(46);
    vertices[41].addNeighbor(47);

    vertices[42].addNeighbor(38);
    vertices[42].addNeighbor(47);

    vertices[43].addNeighbor(39);
    vertices[43].addNeighbor(40);
    vertices[43].addNeighbor(48);

    vertices[44].addNeighbor(40);
    vertices[44].addNeighbor(41);
    vertices[44].addNeighbor(49);

    vertices[45].addNeighbor(41);
    vertices[45].addNeighbor(42);
    vertices[45].addNeighbor(50);

    vertices[46].addNeighbor(42);
    vertices[46].addNeighbor(43);
    vertices[46].addNeighbor(51);

    vertices[47].addNeighbor(44);
    vertices[47].addNeighbor(52);

    vertices[48].addNeighbor(45);
    vertices[48].addNeighbor(52);
    vertices[48].addNeighbor(53);

    vertices[49].addNeighbor(46);
    vertices[49].addNeighbor(53);
    vertices[49].addNeighbor(54);

    vertices[50].addNeighbor(47);
    vertices[50].addNeighbor(54);

    vertices[51].addNeighbor(48);
    vertices[51].addNeighbor(49);

    vertices[52].addNeighbor(49);
    vertices[52].addNeighbor(50);

    vertices[53].addNeighbor(50);
    vertices[53].addNeighbor(51);
}


int Board::getNumVertices()const{
    return vertices.size();
}
   
int Board::getNumPathes()const{
    return pathes.size();
}

std::vector<Path> Board::getPaths() const {
    return pathes;
}

// Method to distribute resources to players based on dice roll
void Board::distributeResources(int diceRoll, Player& p1, Player& p2, Player& p3) {
    std::vector<Player*> players = { &p1, &p2, &p3 }; // Create a vector of player pointers

    // Handle the case where a 7 is rolled
    if (diceRoll == 7) {
        for (Player* player : players) {
            if (player->getResources().size() > 7) { // Check if player has more than 7 resources
                discardResources(*player); // Discard excess resources
            } else {
                std::cout << "No players need to discard resources." << std::endl;
            }
        }
        return; // Exit the function as no further resource distribution is needed
    }

    // Find tiles corresponding to the dice roll number
    auto it = numberTiles.find(diceRoll);
    if (it != numberTiles.end()) { // If tiles corresponding to the dice roll number are found
        for (const Tile& tile : it->second) { // Iterate over the tiles
            Resource resource = tile.getResource(); // Get the resource from the tile
            std::cout << "Distributing " << tile.getResourceType() << " resources..." << std::endl;

            for (Player* player : players) { // Iterate over the players
                for (Building* building : player->getBuildings()) { // Iterate over the buildings of the player
                    int vertexIndex = building->getVertex(); // Get the vertex index of the building

                    // Handle resource distribution for cities
                    if (building->getType() == CITY) {
                        const Vertex& vertex = getVertexFromIndex(vertexIndex); // Get the vertex from the index
                        if (vertex.isAdjacentToTile(tile)) { // Check if the vertex is adjacent to the tile
                            player->addResource(resource, 2); // Add 2 resources to the player
                            std::cout << player->getName() << " received 2 " << tile.getResourceType() << std::endl;
                        }
                    // Handle resource distribution for settlements
                    } else if (building->getType() == SETTLEMENT) {
                        const Vertex& vertex = getVertexFromIndex(vertexIndex); // Get the vertex from the index
                        if (vertex.isAdjacentToTile(tile)) { // Check if the vertex is adjacent to the tile
                            player->addResource(resource, 1); // Add 1 resource to the player
                            std::cout << player->getName() << " received 1 " << tile.getResourceType() << std::endl;
                        }
                    }
                }
            }
        }
    } else {
        std::cout << "No tiles with the number " << diceRoll << " found." << std::endl;
    }
}

void Board::discardResources(Player& p) {
    int totalResources = p.getResources().size();
    int resourcesToDiscard = totalResources / 2;
    std::cout << p.getName() << " needs to discard " << resourcesToDiscard << " resource cards." << std::endl;

    // Discard resources in arbitrary order; in a real game, the player would choose
        for (auto& pair : p.getResources()) {

            // Exit the loop if no more resources need to be discarded
            if (resourcesToDiscard <= 0){
                break;
            }
            
            // Determine the amount of resources to discard: the minimum between what the player has and what needs to be discarded
            int discardAmount = std::min(pair.second, resourcesToDiscard);
            
            // Subtract the resources from the player
            p.addResource(pair.first, -discardAmount);
            
            // Update the amount of resources left to discard
            resourcesToDiscard -= discardAmount;
    }
}

// Method to get a vertex from its index
const Vertex& Board::getVertexFromIndex(int nodeIndex) const {
    if (nodeIndex >= 0 && nodeIndex < vertices.size()) { // Check if the index is within bounds
        return vertices[nodeIndex - 1]; // Return the vertex (adjusting index as needed)
    } else {
        std::cout << "Vertex " << nodeIndex << " is invalid" << std::endl;
        return vertices.back(); // Return the last vertex as a fallback
    }
}

// Method to get a path from source and target indices
const Path& Board::getPathFromIndexes(int source, int target) const {
    for (int i = 0; i < pathes.size(); i++) { // Iterate over all paths
        if ((pathes[i].getSource() == source && pathes[i].getTarget() == target) ||
            (pathes[i].getSource() == target && pathes[i].getTarget() == source)) {
            return pathes[i]; // Return the path if it matches the source and target
        }
    }
    return pathes.back(); // Return the last path as a fallback
}

// Method to place a piece (road, settlement, or city) on the board
void Board::putPieceOnTheBoard(Building* build, int sourceVertex, int targetVertex) {
    if (build->getType() == ROAD) { // If the building is a road
        for (int i = 0; i < pathes.size(); i++) { // Iterate over all paths
            if ((pathes[i].getSource() == sourceVertex && pathes[i].getTarget() == targetVertex) ||
                (pathes[i].getSource() == targetVertex && pathes[i].getTarget() == sourceVertex)) {
                pathes[i].setBuilding(build); // Set the building on the path
                std::cout << build->getOwnerName() << " built road (" << sourceVertex << "->" << targetVertex << ")." << std::endl;
            }
        }
    } else if (build->getType() == SETTLEMENT) { // If the building is a settlement
        vertices[sourceVertex - 1].setBuilding(build); // Set the building on the vertex
        std::cout << build->getOwnerName() << " built settlement on vertex " << sourceVertex << "." << std::endl;
    } else if (build->getType() == CITY) { // If the building is a city
        vertices[sourceVertex - 1].setBuilding(build); // Set the building on the vertex
        std::cout << build->getOwnerName() << " built city on vertex " << sourceVertex << "." << std::endl;
    }
}

// Method to print the board state
void Board::printBoard() const {
    for (const Vertex& vertex : vertices) {
        if (vertex.hasBuilding()) {
            std::cout << "Vertex " << vertex.getNumIndex() << " has a " << vertex.getBuilding()->getBuildingTypeName()
                      << " owned by " << vertex.getBuilding()->getOwnerName() << std::endl;
        }
    }

    for (const Path& path : pathes) {
        if (path.hasRoad()) {
            std::cout << "Path (" << path.getSource() << " -> " << path.getTarget() << ") has a road built by "
                      << path.getBuilding()->getOwnerName() << std::endl;
        }
    }
}


// Method to check if there's a road on a given edge
bool Board::hasRoadOnEdge(int vertex1, int vertex2) const {
    const Path& path = getPathFromIndexes(vertex1, vertex2);
    return path.hasRoad();
}

// Method to check if there's a settlement on a given vertex
bool Board::hasSettlementOnVertex(int vertexInd) const {
    const Vertex& vertex = getVertexFromIndex(vertexInd);
    return vertex.hasSettlement();
}

// Method to check if there's a city on a given vertex
bool Board::hasCityOnVertex(int vertexInd) const {
    const Vertex& vertex = getVertexFromIndex(vertexInd);
    return vertex.hasCity();
}