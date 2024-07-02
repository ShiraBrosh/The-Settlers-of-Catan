#include "MonopolyCard.hpp"
#include <iostream>
#include <unordered_map>
#include <limits> // הוספת הכנסה זו

MonopolyCard::MonopolyCard() : DevelopmentCard("Monopoly") {}
void MonopolyCard::use(Player* player, const std::vector<Player*>& allPlayers) const {
    std::cout << "Played Monopoly card. You gain all resources of the type yoe have at small from other players!" << std::endl;
    
    // Find the resource type the player has the least amount of
    const std::unordered_map<Resource, int>& resources = player->getResources();
    Resource chosenResource;
    int minAmount = std::numeric_limits<int>::max(); 


    for (const auto& resource : resources) {
        if (resource.second < minAmount) {
            minAmount = resource.second;
            chosenResource = resource.first;
        }
    }
    // Current player (this)
    Player* currentPlayer = player;

    int sum=0;
    // Collect all resources of the chosen type from other players
    for (Player* player : allPlayers) {
        if (player != currentPlayer) {
            int amount = player->getResources().at(chosenResource);
            sum=sum+amount;
            player->addResource(chosenResource, -amount);
            currentPlayer->addResource(chosenResource, amount);
        }
    }

    std::cout<< "the player get: "<< sum <<" "<<  Tile::resourceToString(chosenResource) << std::endl;

}
