/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef ROAD_HPP
#define ROAD_HPP

#include "Building.hpp"  
#include "Path.hpp"      
#include <vector>        

// Forward declaration
class Player;             
class Board;              

class Road : public Building {  // Road class inherits from Building class

private:
    int target;  // Private member variable representing the target vertex of the road

public:
    // Constructor: initializes a road with its owner, source vertex, and target vertex
    Road(Player* owner, int source, int target);

    // Destructor: prints a message when a road object is destroyed
    virtual ~Road() override;

    // Getter function to retrieve the target vertex of the road
    int getTarget() const;

    // Function to attempt to build a road between two vertices on the board
    bool buildRoad(Player* player, int numSource, int numTarget, Board& board);

    // Helper function to check if the player can connect a road to their own settlement, city, or road
    bool connectOwnerBuild(Player* player, int numSource, int numTarget, Board& board);

    // Function to retrieve a vector of paths that are connected to this road on the board
    std::vector<Path*> getConnectedRoads(const Board& board) const;

};

#endif // ROAD_HPP
