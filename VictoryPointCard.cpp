/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "VictoryPointCard.hpp"
#include <iostream>

VictoryPointCard::VictoryPointCard() : DevelopmentCard("VictoryPoint") {}

VictoryPointCard::~VictoryPointCard() {}

void VictoryPointCard::use(Player* player, const std::vector<Player*>& allPlayers) const {
    // Display a message indicating the card's effect
    std::cout << "Played VictoryPointCard. Player " << player->getName() << " gets 1 victory point!" << std::endl;
    
    // Increase the player's victory points by 1
    player->addToVictoryPoints(1);
}
