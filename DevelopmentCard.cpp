/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "DevelopmentCard.hpp"

// Constructor with parameter to initialize the name of the card
DevelopmentCard::DevelopmentCard(const std::string& name) : name(name) {}

// destructor for polymorphic behavior
DevelopmentCard::~DevelopmentCard() {}

// Getter for the name of the card
std::string DevelopmentCard::getName() const {
    return name;
}

