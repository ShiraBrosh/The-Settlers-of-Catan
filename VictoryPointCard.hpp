/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef VICTORYPOINTCARD_HPP
#define VICTORYPOINTCARD_HPP

#include "DevelopmentCard.hpp"

class VictoryPointCard : public DevelopmentCard {
public:
    VictoryPointCard(); // Constructor
    virtual ~VictoryPointCard() override; // Destructor
    void use(Player* player, const std::vector<Player*>& allPlayers) const override; // Override the use method from DevelopmentCard
};

#endif // VICTORYPOINTCARD_HPP
