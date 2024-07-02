#ifndef CITY_HPP
#define CITY_HPP

#include <iostream>

#include "Building.hpp"
#include "Player.hpp"

class Building;

class City : public Building {

public:
    City(Player* owner, int vertex);
    ~City();

    const int getVertex() const;
    bool upgradeToCity(Player* player, int numVertex, Board& board);


};

 #endif