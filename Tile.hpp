// Tile.hpp

#ifndef TILE_HPP
#define TILE_HPP

#include <string>

enum Resource {
    WOOD,
    BRICK,
    SHEEP,
    WHEAT,
    IRON,
    DESERT,
    UNKNOWN
};

class Tile {
private:
    Resource resource;
    int number;

public:
    Tile(Resource resource, int number);
    Resource getResource() const;
    std::string getResourceType() const;
    int getNumber() const;
    static std::string resourceToString(Resource resource);


};

#endif // TILE_HPP
