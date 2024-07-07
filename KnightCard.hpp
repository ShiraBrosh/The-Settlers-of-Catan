/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef KNIGHTCARD_HPP
#define KNIGHTCARD_HPP

#include "DevelopmentCard.hpp"

// Class representing a Knight development card, inheriting from DevelopmentCard
class KnightCard : public DevelopmentCard {
public:
    KnightCard(); // Constructor
    virtual ~KnightCard() override; // Destructor
    
    static int biggestArmy; // Static variable tracking the size of the largest army
    static Player* whoHavebiggestArmy; // Static variable tracking the player with the largest army
    
    // Override of the use method from DevelopmentCard
    void use(Player* player, const std::vector<Player*>& allPlayers) const override;
};

#endif // KNIGHTCARD_HPP
