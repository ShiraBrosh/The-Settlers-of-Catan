#ifndef SETTLEMENT_HPP
#define SETTLEMENT_HPP

#include <iostream>
#include <vector>
#include "Building.hpp"

class Player;
class Board;
class Vertex;
class Path;

class Settlement : public Building {

public:
    Settlement(Player* owner, int vertex);
    ~Settlement();

    int getVertex() const;
    bool buildSettlement(Player* player, int numVertex, Board& board);
    std::vector<Path*> getConnectedRoads(const Board& board) const;



};

 #endif