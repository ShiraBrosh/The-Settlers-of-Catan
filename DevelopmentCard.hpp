/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

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
    // Constructor to initialize a development card with a given name
    DevelopmentCard(const std::string& name);

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~DevelopmentCard();

    // Pure virtual function for using the development card, to be implemented in derived classes
    virtual void use(Player* player, const std::vector<Player*>& allPlayers) const = 0;

    // Getter method to retrieve the name of the development card
    std::string getName() const;
};

#endif // DEVELOPMENTCARD_HPP
