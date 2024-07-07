/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "MonopolyCard.hpp"
#include <iostream>
#include <unordered_map>
#include <limits> // Added for numeric_limits

MonopolyCard::MonopolyCard() : DevelopmentCard("Monopoly") {}

MonopolyCard::~MonopolyCard() {}

void MonopolyCard::use(Player* player, const std::vector<Player*>& allPlayers) const {
    std::cout << "Played Monopoly card. You gain all resources of the type you have the least from other players!" << std::endl;

    // Find the resource type the player has the least amount of
    const std::unordered_map<Resource, int>& resources = player->getResources();
    Resource chosenResource;
    int minAmount = std::numeric_limits<int>::max(); // Initialize to maximum possible integer value

    for (const auto& resource : resources) {
        if (resource.second < minAmount) {
            minAmount = resource.second;
            chosenResource = resource.first;
        }
    }

    // Current player (this)
    Player* currentPlayer = player;
    int totalAmountGained = 0;

    // Collect all resources of the chosen type from other players
    for (Player* otherPlayer : allPlayers) {
        if (otherPlayer != currentPlayer) {
            int amount = otherPlayer->getResources().at(chosenResource); // Get amount of chosen resource from other player
            otherPlayer->addResource(chosenResource, -amount); // Remove resource from other player
            currentPlayer->addResource(chosenResource, amount); // Add resource to current player
            totalAmountGained += amount; // Track total amount gained
        }
    }

    // Print the total amount of resources gained and the resource type
    std::cout << "You gained: " << totalAmountGained << " " << Tile::resourceToString(chosenResource) << std::endl;
}
