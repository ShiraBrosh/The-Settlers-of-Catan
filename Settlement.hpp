/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef SETTLEMENT_HPP
#define SETTLEMENT_HPP

#include <iostream>     
#include <vector>       
#include "Building.hpp" 

// Forward declarations
class Player;
class Board;
class Vertex;
class Path;

class Settlement : public Building {
public:
    Settlement(Player* owner, int vertex);
    // Constructor: Initializes a Settlement with its owner and vertex

    virtual ~Settlement() override;
    // Destructor: Virtual destructor to properly manage memory of derived classes

    int getVertex() const;
    // Function to retrieve the vertex index where the Settlement is built

    bool buildSettlement(Player* player, int numVertex, Board& board);
    // Function to build a Settlement for a player on a specified vertex

    std::vector<Path*> getConnectedRoads(const Board& board) const;
    // Function to retrieve all roads connected to the settlement's vertex on the board

};

#endif // SETTLEMENT_HPP
