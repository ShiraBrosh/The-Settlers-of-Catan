#include "Building.hpp"
#include "Player.hpp"  // הוסיפו שורה זו

Building::Building(BuildingType type, Player* owner, int vertex)
    : type(type), owner(owner), vertexInd(vertex) {}

BuildingType Building::getType() const {
    return type;
}

Player* Building::getOwner() const {
    return owner;
}

std::string Building::getOwnerName() const {
    if (owner != nullptr) {
        return owner->getName();
    } else {
        std::cerr << "Error: Building owner is null!" << std::endl;
        return "Unknown";
    }
}


const int Building::getVertex() const {
    return vertexInd;
}    

bool Building::isEmpty() const {
    return (type == NONE);
}

std::string Building::getBuildingTypeName() const {
    switch (type) {
        case SETTLEMENT:
            return "Settlement";
        case CITY:
            return "City";
        case ROAD:
            return "Road";
        default:
            return "Unknown";
    }
}

