#ifndef ROAD_HPP
#define ROAD_HPP

#include "Building.hpp"
#include "Path.hpp"
#include <vector>

class Player;
class Board;

class Road : public Building {
public:
    Road(Player* owner, int source, int target);
    ~Road();

    int getTarget() const;
    bool buildRoad(Player* player, int numSource, int numTarget, Board& board);
    bool connectOwnerBuild(Player* player, int numSource, int numTarget, Board& board);
    std::vector<Path*> getConnectedRoads(const Board& board) const;


private:
    int target;
};

#endif // ROAD_HPP
