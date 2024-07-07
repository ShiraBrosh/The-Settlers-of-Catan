/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "RoadBuildingCard.hpp"  
#include <iostream>             
#include "Katan.hpp"             
#include "Board.hpp"             
#include "Player.hpp"            

// Constructor: initializes the RoadBuildingCard with its type name
RoadBuildingCard::RoadBuildingCard() : DevelopmentCard("RoadBuilding") {
}

// Destructor
RoadBuildingCard::~RoadBuildingCard() {
}

// Function to use the RoadBuildingCard by building two additional roads for the player
void RoadBuildingCard::use(Player* player, const std::vector<Player*>& allPlayers) const {

    // Print a message indicating that the Road Building card is played
    std::cout << "Played Road Building card. Build two additional roads!" << std::endl;

    // Get the game board from the context using Katan singleton instance and all players
    Board& board = Katan::getInstance(*allPlayers[0], *allPlayers[1], *allPlayers[2]).getBoard();

    // For testing purposes, predefined road locations are used
    std::vector<std::pair<int, int>> roads = { {1, 4}, {2, 3} };

    // Build two additional roads for the player at the predefined locations
    for (const auto& road : roads) {
        player->buildRoad(road.first, road.second, board);
    }
}

