/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include "Building.hpp"
#include "Tile.hpp"
#include "Path.hpp"
#include "Board.hpp"

class Board; // Forward declaration of Board class

class Vertex {
private:
    int numIndex;               // Index of the vertex
    Building* building;         // Building constructed on the vertex, if any
    std::vector<Tile> tileList; // List of tiles associated with the vertex
    std::vector<Path> pathsList;// List of paths connected to the vertex
    std::vector<int> neighborsList; // List of neighboring vertices indices

public:
    Vertex();   // Default constructor
    Vertex(const std::vector<Tile>& tileList, const std::vector<Path>& pathsList, int numIndex);
    // Constructor that initializes the vertex with tiles, paths, and index

    ~Vertex();  // Destructor

    int getNumIndex() const;
    // Getter for the index of the vertex

    Building* getBuilding() const;
    // Getter for the building constructed on the vertex

    const std::vector<int>& getNeighbors() const;
    // Getter for the indices of neighboring vertices

    const std::vector<Path>& getPaths() const;
    // Getter for the paths connected to the vertex

    std::vector<Path> getPathsForRoads() const;
    // Return paths that have roads

    void setBuilding(Building* newBuilding);
    // Setter for the building constructed on the vertex

    bool hasBuilding() const;
    // Check if there is a building on the vertex

    bool hasSettlement() const;
    // Check if there is a settlement on the vertex

    bool hasCity() const;
    // Check if there is a city on the vertex

    bool hasAdjacentSettlement(const Board& board) const;
    // Check if there is an adjacent settlement to this vertex

    bool isAdjacentToTile(Tile tile) const;
    // Check if this vertex is adjacent to a given tile

    void addNeighbor(int numVertex);
    // Add a neighbor to this vertex if it doesn't already exist in the neighbors list

};

#endif // VERTEX_HPP
