/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map> 
#include "Tile.hpp"
#include "Building.hpp"
#include "Player.hpp"
#include "Vertex.hpp"
#include "Path.hpp"

// Forward declaration of the Vertex class
class Vertex;
class Tile;

class Board {
private:
    std::vector<Tile> tiles; // Vector to store tiles
    std::vector<Vertex> vertices; // Vector of vertices with resources
    std::vector<Path> pathes; // Vector of paths connecting vertices

    // Map to associate dice roll numbers with corresponding tiles
    std::unordered_map<int, std::vector<Tile>> numberTiles;

    // Initialization functions for vertices, paths, and neighbors
    void initializeVertices(); // Declaration for the function to initialize vertices
    void initializePaths(); // Declaration for the function to initialize paths
    void initializeNeighbors(); // Declaration for the function to initialize neighbors

public:
    Board(); // Constructor
    ~Board(); // Destructor

    void initialize(); // Function to initialize the board
    void printBoard() const; // Function to print the board
    void printBuilding() const; // Function to print buildings
    std::vector<Path> getPaths() const; // Function to get all paths
    int getNumVertices() const; // Function to get the number of vertices
    int getNumPathes() const; // Function to get the number of paths

    // Function to distribute resources to players based on dice roll
    void distributeResources(int diceRoll, Player& p1, Player& p2, Player& p3);
    
    // Function to discard resources from a player
    void discardResources(Player& p);

    // Function to get a vertex from its index
    const Vertex& getVertexFromIndex(int nodeIndex) const;

    // Function to get a path from source and target indices
    const Path& getPathFromIndexes(int source, int target) const;

    // Function to place a piece (road, settlement, or city) on the board
    void putPieceOnTheBoard(Building* build, int sourceVertex, int targetVertex);

    // Function to check if there's a road on the edge between two vertices
    bool hasRoadOnEdge(int vertex1, int vertex2) const;

    // Function to check if there's a settlement on a vertex
    bool hasSettlementOnVertex(int vertex) const;

    // Function to check if there's a city on a vertex
    bool hasCityOnVertex(int vertex) const;
};

#endif // BOARD_HPP
