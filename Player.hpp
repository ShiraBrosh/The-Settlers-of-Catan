#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include <unordered_map> 
#include "Tile.hpp"
#include "DevelopmentCard.hpp"

class DevelopmentCard;
class Building;
class Settlement;
class Road;
class Board;

class Player {
private:
    std::string name;
    std::vector<Building*> buildings;
    std::unordered_map<Resource, int> resources;
    std::vector<DevelopmentCard*> developmentCards;
    int victoryPoints;
    bool isTurn;
    int roadsBuilt; 
    int countKnights=0;

  // Private helper functions
    bool hasEnoughResources(Resource type, int amount) const;

public:
    Player(std::string name);
    std::string getName()const ;
    const bool getTurn() const ; 
    int getCountKnights();
    int getVictoryPoints() const ;
    std::vector<Building*> getBuildings() const;
    const std::unordered_map<Resource, int>& getResources() const;
    std::vector<DevelopmentCard*>& getDevelopmentCards();
    
    void removeBuilding(Building* building);

    void setTurn(bool turn);
    void addCountKnights();
    void addDevelopmentCard(DevelopmentCard *card);
    void addToVictoryPoints(int victory);
    void removeVictoryPoints(int victory);
    int rollDice();
    void addResource(Resource r, int amount);
    int countDevelopmentCard(std::string nameCard);

    void buildSettlement(int numVertex, Board& board);
    void buildRoad(int numSource, int numTarget, Board& board);
    void buildCity(int numVertex, Board& board);
    void buildDevelopmentCard();

    bool trade(Player* otherPlayer, Resource offer, Resource request, int offerCount, int requestCount);


    void deductResourcesForRoad();
    void deductResourcesForSettlement();
    void deductResourcesForCity();
    void deductResourcesForDevelopmentCard();
    void deductResource(Resource type, int amount);

    void printBuildings() const;
    void printResources() const;
    static void setBiggestArmy(Player* player);
    void drawDevelopmentCard();
    bool hasWon() const;

};

#endif // PLAYER_HPP
