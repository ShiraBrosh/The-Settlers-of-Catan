#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <iostream>

class Player;

enum BuildingType { NONE, SETTLEMENT, CITY, ROAD };

class Building {
 protected:
     BuildingType type;
     Player* owner;
     int vertexInd;

 public:
     Building(BuildingType type, Player* owner, int vertex);

     BuildingType getType() const;
     Player* getOwner() const;
     std::string getOwnerName() const;
     const int getVertex() const;

     bool isEmpty() const;
     std::string getBuildingTypeName() const;
 };

 #endif // BUILDING_HPP
