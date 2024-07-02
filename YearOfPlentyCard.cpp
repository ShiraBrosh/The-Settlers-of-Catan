#include "YearOfPlentyCard.hpp"
#include "Tile.hpp"
#include <iostream>
#include <limits> // For std::numeric_limits


YearOfPlentyCard::YearOfPlentyCard() : DevelopmentCard("YearOfPlenty") {}

void YearOfPlentyCard::use(Player* player, const std::vector<Player*>& allPlayers) const {
    std::cout << "Played Year of Plenty card. You receive two resources of your choice from the bank!" << std::endl;

    const std::unordered_map<Resource, int>& resources = player->getResources();
    
    // Find the two resources with the lowest amount
    Resource firstResource = Resource::WOOD; // Initialize with some resource
    Resource secondResource = Resource::WOOD; // Initialize with some resource

    int firstMin = std::numeric_limits<int>::max();
    int secondMin = std::numeric_limits<int>::max();

    for (const auto& resourcePair : resources) {
        int amount = resourcePair.second;
        if (amount < firstMin) {
            secondMin = firstMin;
            secondResource = firstResource;

            firstMin = amount;
            firstResource = resourcePair.first;
        } else if (amount < secondMin) {
            secondMin = amount;
            secondResource = resourcePair.first;
        }
    }

    // Add the chosen resources to the player's resources
    player->addResource(firstResource, 1);
    player->addResource(secondResource, 1);

    std::cout<<"the player get: 1 " << Tile::resourceToString(firstResource) << " and 1 "<< Tile::resourceToString(secondResource)<< std::endl;
}