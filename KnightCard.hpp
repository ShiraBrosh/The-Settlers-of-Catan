#ifndef KNIGHTCARD_HPP
#define KNIGHTCARD_HPP

#include "DevelopmentCard.hpp"

class KnightCard : public DevelopmentCard {
public:
    KnightCard(); // Constructor
    static int biggestArmy; // הצבא הגדול ביותר
    static Player* whoHavebiggestArmy; // השחקן שיש לו את הצבא הגדול ביותר
    void use(Player* player, const std::vector<Player*>& allPlayers) const override; // Override the use method from DevelopmentCard
};

#endif // KNIGHTCARD_HPP
