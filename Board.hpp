#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Tile.hpp"
#include "Building.hpp"
#include "Player.hpp"
#include "Vertex.hpp"
#include "Path.hpp"

class Vertex;

class Board {
private:
    std::vector<Tile> tiles;
    std::vector<Vertex> vertices; // Vector of vertices with resources
    std::vector<Path> pathes; // Vector of vertices with resources

    std::unordered_map<int, std::vector<Tile>> numberTiles;

    void initializeVertices(); // Declaration for the function
    void initializePaths();
    void initializeNeighbors();

public:
    Board();
    void initialize();
    void printBoard() const;
    void printBuilding() const;
    std::vector<Path> getPaths() const;
    int getNumVertices()const;
    int getNumPathes()const;
    void distributeResources(int diceRoll, Player& p1, Player& p2, Player& p3);
    void discardResources(Player& p);
    const Vertex& getVertexFromIndex(int nodeIndex) const;
    const Path& getPathFromIndexes(int source, int target) const ;
    void putPieceOnTheBoard(Building* build, int sourceVertex, int targetVertex);
    bool hasRoadOnEdge(int vertex1, int vertex2) const;
    bool hasSettlementOnVertex(int vertex) const;
    bool hasCityOnVertex(int vertex) const;



    
};

#endif // BOARD_HPP
