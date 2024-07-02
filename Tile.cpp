// Tile.cpp

#include "Tile.hpp"

Tile::Tile(Resource resource, int number) : resource(resource), number(number) {}

Resource Tile::getResource() const {
    return resource;
}

std::string Tile::getResourceType() const {
    switch (resource) {
        case WOOD:
            return "WOOD";
        case BRICK:
            return "BRICK";
        case SHEEP:
            return "SHEEP";
        case WHEAT:
            return "WHEAT";
        case IRON:
            return "IRON";
        case DESERT:
            return "DESERT";
        default:
            return "UNKNOWN";
    }
}

int Tile::getNumber() const{
    return number;
}

std::string Tile::resourceToString(Resource resource) {
    switch (resource) {
        case WOOD: return "WOOD";
        case BRICK: return "BRICK";
        case SHEEP: return "SHEEP";
        case WHEAT: return "WHEAT";
        case IRON: return "IRON";
        case DESERT: return "DESERT";
        default: return "UNKNOWN";
    }
}