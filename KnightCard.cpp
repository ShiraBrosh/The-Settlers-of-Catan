#include "KnightCard.hpp"
#include <iostream>


int KnightCard::biggestArmy = 2; // ערך הצבא הגדול ביותר בברירת מחדל
Player* KnightCard::whoHavebiggestArmy = nullptr;


KnightCard::KnightCard() : DevelopmentCard("Knight") {}

void KnightCard::use(Player* player, const std::vector<Player*>& allPlayers) const {

   player->addCountKnights();
        if (player->getCountKnights() > biggestArmy) {
            if (whoHavebiggestArmy) {
                whoHavebiggestArmy->removeVictoryPoints(2);
            }

            biggestArmy = player->getCountKnights();
            whoHavebiggestArmy = player;
            player->addToVictoryPoints(2);
        }
} 
