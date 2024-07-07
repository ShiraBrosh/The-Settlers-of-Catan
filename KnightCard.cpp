/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/
#include "KnightCard.hpp"
#include <iostream>

// Default value for the biggest army size
int KnightCard::biggestArmy = 2;

// Default player with the biggest army
Player* KnightCard::whoHavebiggestArmy = nullptr;

// Constructor initializing the development card with the name "Knight"
KnightCard::KnightCard() : DevelopmentCard("Knight") {}

// Destructor
KnightCard::~KnightCard() {}

// Implementation of the use function for the Knight card
void KnightCard::use(Player* player, const std::vector<Player*>& allPlayers) const {
    // Increase the player's count of knights
    player->addCountKnights();

    // Check if the player now has the largest army
    if (player->getCountKnights() > biggestArmy) {
        // If another player previously had the largest army, reduce their victory points
        if (whoHavebiggestArmy) {
            whoHavebiggestArmy->removeVictoryPoints(2);
        }

        // Update the new biggest army size and player
        biggestArmy = player->getCountKnights();
        whoHavebiggestArmy = player;
        
        // Award the current player with victory points for having the largest army
        player->addToVictoryPoints(2);
    }
}
