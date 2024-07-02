#include "Path.hpp"
#include "Building.hpp"
#include <iostream>

// Constructor
Path::Path(int source, int target) : source(source), target(target), road(nullptr) {}

int Path::getSource() const{
    return source;
}

int Path::getTarget() const {
    return target;
}

bool Path::hasRoad() const { 
    return road != nullptr; }

Building* Path::getBuilding() const{
    return road;
}

void Path::setBuilding(Building* building) {
    road = building;
}
