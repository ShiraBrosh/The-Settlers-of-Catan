/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef ROADBUILDINGCARD_HPP
#define ROADBUILDINGCARD_HPP

#include "DevelopmentCard.hpp"

class RoadBuildingCard : public DevelopmentCard {
public:
    RoadBuildingCard(); // Constructor
    virtual ~RoadBuildingCard() override; //Destructor

    void use(Player* player, const std::vector<Player*>& allPlayers) const override; // Override the use method from DevelopmentCard
};

#endif // ROADBUILDINGCARD_HPP
