/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#pragma once

#include "DevelopmentCard.hpp"

class MonopolyCard : public DevelopmentCard {
public:
    MonopolyCard(); // Constructor
    virtual ~MonopolyCard() override; // Destructor
    void use(Player* player, const std::vector<Player*>& allPlayers) const override; // Override the use method from DevelopmentCard
};
