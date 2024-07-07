/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "Path.hpp" 
#include "Building.hpp" 
#include <iostream> 

// Constructor: Initializes a Path object with given source and target vertices
Path::Path(int source, int target) : source(source), target(target), road(nullptr) {}

// Destructor: Cleans up resources owned by the Path object
Path::~Path() {}

// Getter for the source vertex index of the path
int Path::getSource() const {
    return source;
}

// Getter for the target vertex index of the path
int Path::getTarget() const {
    return target;
}

// Checks if there is a road (Building object) on this path
bool Path::hasRoad() const {
    return road != nullptr;
}

// Getter for the Building object representing the road on this path
Building* Path::getBuilding() const {
    return road;
}

// Setter for the Building object representing the road on this path
void Path::setBuilding(Building* building) {
    road = building;
}

