#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include "Player.hpp"
#include "Katan.hpp"

#include <iostream>
#include <string>

// Base class representing a development card
class DevelopmentCard {
protected:
    std::string name; // Name of the development card

public:
    DevelopmentCard(const std::string& name);
    virtual ~DevelopmentCard();

    virtual void use(Player* player, const std::vector<Player*>& allPlayers) const = 0; // פונקציה וירטואלית טהורה לשימוש בקלף
    std::string getName() const;
};

#endif // DEVELOPMENTCARD_HPP
