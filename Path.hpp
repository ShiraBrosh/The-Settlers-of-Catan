#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include "Tile.hpp"
#include "Building.hpp"

class Building;


class Path {

private:
    int source;
    int target;
    Building* road; // Road on the path

public:
    Path(int source, int target);

    int getSource() const;
    int getTarget() const;
    Building* getBuilding() const;
    bool hasRoad() const; 
    void setBuilding(Building* building);
};

#endif // PATH_HPP
