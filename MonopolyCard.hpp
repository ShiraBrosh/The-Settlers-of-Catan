#pragma once MONOPOLYCARD_HPP

#include "DevelopmentCard.hpp"

class MonopolyCard : public DevelopmentCard {
public:
    MonopolyCard(); // Constructor

    void use(Player* player, const std::vector<Player*>& allPlayers) const override; // Override the use method from DevelopmentCard
};

