/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef PATH_HPP
#define PATH_HPP

#include <vector> // Include necessary header for std::vector
#include "Tile.hpp" // Include necessary header for Tile class
#include "Building.hpp" // Include necessary header for Building class

class Building; // Forward declaration of Building class to avoid circular inclusion

class Path {
private:
    int source; // Source vertex index of the path
    int target; // Target vertex index of the path
    Building* road; // Pointer to the Building object representing a road on this path

public:
    // Constructor
    Path(int source, int target);

    // Destructor
    ~Path();

    // Getter for source vertex index
    int getSource() const;

    // Getter for target vertex index
    int getTarget() const;

    // Getter for the Building object representing the road on this path
    Building* getBuilding() const;

    // Checks if a road (Building object) exists on this path
    bool hasRoad() const;

    // Setter for the Building object representing the road on this path
    void setBuilding(Building* building);
};

#endif // PATH_HPP
