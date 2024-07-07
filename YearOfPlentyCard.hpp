/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include "DevelopmentCard.hpp"

class YearOfPlentyCard : public DevelopmentCard {
public:
    YearOfPlentyCard(); // Constructor
    virtual ~YearOfPlentyCard() override; // Destructor
    void use(Player* player, const std::vector<Player*>& allPlayers) const override; // Override the use method from DevelopmentCard
};

#endif // YEAROFPLENTYCARD_HPP
