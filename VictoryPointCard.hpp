#ifndef MONOPOLYCARD_HPP
#define MONOPOLYCARD_HPP

#include "DevelopmentCard.hpp"

class VictoryPointCard : public DevelopmentCard {
public:
    VictoryPointCard(); // Constructor

    void use(Player* player, const std::vector<Player*>& allPlayers) const override; // Override the use method from DevelopmentCard
    //DevelopmentCard clone() const { return new monopol(*this); }
};

#endif // MONOPOLYCARD_HPP
