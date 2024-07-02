#include "VictoryPointCard.hpp"
#include <iostream>

VictoryPointCard::VictoryPointCard() : DevelopmentCard("VictoryPoint") {}

void VictoryPointCard::use(Player* player, const std::vector<Player*>& allPlayers) const {
    std::cout << "Played VictoryPointCard card. get 1 victory point!" << std::endl;
    player->addToVictoryPoints(1);
}
