#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include "Building.hpp"
#include "Tile.hpp"
#include "Path.hpp"
#include "Board.hpp"

class Board;

class Vertex {
private:
    int numIndex;
    Building* building;
    std::vector<Tile> tileList;
    std::vector<Path> pathsList;
    std::vector<int> neighborsList; // רשימת השכנים של כל קודקוד


public:
    Vertex();
    Vertex(const std::vector<Tile>& tileList, const std::vector<Path>& pathsList, int numIndex);
    ~Vertex();

    int getNumIndex() const;
    Building* getBuilding() const;
    const std::vector<int>& getNeighbors() const;
    const std::vector<Path>& getPaths() const; 
    std::vector<Path> getPathsForRoads() const;
    void setBuilding(Building* newBuilding);
    bool hasBuilding() const;
    bool hasSettlement() const;
    bool hasCity() const;
    bool hasAdjacentSettlement(const Board& board) const;
    bool isAdjacentToTile(Tile tile) const ;
    void addNeighbor(int numVertex);


};

#endif
