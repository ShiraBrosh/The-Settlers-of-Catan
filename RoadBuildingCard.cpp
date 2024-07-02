#include "RoadBuildingCard.hpp"
#include <iostream>

RoadBuildingCard::RoadBuildingCard() : DevelopmentCard("RoadBuilding") {}


void RoadBuildingCard::use(Player* player, const std::vector<Player*>& allPlayers) const {
    std::cout << "Played Road Building card. Build two additional roads!" << std::endl;

    // Get the board from the game context
    Board& board = Katan::getInstance(*allPlayers[0], *allPlayers[1], *allPlayers[2]).getBoard();

    // For testing, we can use predefined road locations
    std::vector<std::pair<int, int>> roads = { {1, 4}, {2, 3} };

    for (const auto& road : roads) {
        player->buildRoad(road.first, road.second, board);
    }

}