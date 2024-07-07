/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <string>   // For string operations

// Enumeration representing the different types of resources a tile can have
enum Resource {
    WOOD,    // Represents wood resource
    BRICK,   // Represents brick resource
    SHEEP,   // Represents sheep resource
    WHEAT,   // Represents wheat resource
    IRON,    // Represents iron resource
    DESERT,  // Represents desert tile with no resource
    UNKNOWN  // Represents unknown resource type (default)
};

class Tile {
private:
    Resource resource;  // Type of resource on the tile
    int number;         // Number associated with the tile (for number tokens)

public:
    Tile(Resource resource, int number);
    // Constructor: Initializes a tile with a specific resource and number

    ~Tile();
    // Destructor: Cleans up resources, if any

    Resource getResource() const;
    // Function to retrieve the resource type of the tile

    std::string getResourceType() const;
    // Function to retrieve the string representation of the resource type

    int getNumber() const;
    // Function to retrieve the number associated with the tile

    static std::string resourceToString(Resource resource);
    // Static function to convert a Resource enum value to its corresponding string representation

};

#endif // TILE_HPP
