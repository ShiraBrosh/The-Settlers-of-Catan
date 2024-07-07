/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>          
#include <vector>            
#include <unordered_map>     
#include "Tile.hpp"          
#include "DevelopmentCard.hpp" 

// Forward declarations to avoid circular dependencies
class DevelopmentCard;
class Building;
class Settlement;
class Road;
class Board;

class Player {
private:
    std::string name;                          // Player's name
    std::vector<Building*> buildings;          // List of buildings owned by the player
    std::unordered_map<Resource, int> resources; // Map of resources owned by the player
    std::vector<DevelopmentCard*> developmentCards; // List of development cards owned by the player
    int victoryPoints;                         // Player's current victory points
    bool isTurn;                               // Flag indicating if it's the player's turn
    int roadsBuilt;                            // Number of roads built by the player
    int countKnights;                          // Count of knight cards owned by the player

    // Private helper function to check if the player has enough of a specific resource type
    bool hasEnoughResources(Resource type, int amount) const;

public:
    // Constructor: initializes a player with a given name
    Player(std::string name);

    // Destructor: cleans up memory allocated for development cards
    ~Player();

    // Getter for the player's name
    std::string getName() const;

    // Getter for the player's turn status
    const bool getTurn() const;

    // Getter for the count of knight cards owned by the player
    int getCountKnights();

    // Getter for the player's current victory points
    int getVictoryPoints() const;

    // Getter for the player's list of buildings (const version)
    std::vector<Building*> getBuildings() const;

    // Getter for the player's list of buildings (mutable version)
    std::vector<Building*>& getBuildings();

    // Getter for the player's resources map (const version)
    const std::unordered_map<Resource, int>& getResources() const;

    // Getter for the player's list of development cards (mutable version)
    std::vector<DevelopmentCard*>& getDevelopmentCards();

    // Setter for the player's turn status
    void setTurn(bool turn);

    // Increment the count of knight cards owned by the player
    void addCountKnights();

    // Add a development card to the player's collection
    void addDevelopmentCard(DevelopmentCard* card);

    // Add to the player's current victory points
    void addToVictoryPoints(int victory);

    // Remove from the player's current victory points
    void removeVictoryPoints(int victory);

    // Simulate rolling two dice and return their sum
    int rollDice();

    // Add a specified amount of a resource type to the player's resources
    void addResource(Resource r, int amount);

    // Count how many development cards of a specific type the player owns
    int countDevelopmentCard(std::string nameCard);

    // Attempt to build a settlement at a specified vertex on the board
    void buildSettlement(int numVertex, Board& board);

    // Attempt to build a road between two specified vertices on the board
    void buildRoad(int numSource, int numTarget, Board& board);

    // Attempt to upgrade a settlement to a city at a specified vertex on the board
    void buildCity(int numVertex, Board& board);

    // Attempt to buy a development card if the player has enough resources
    void buildDevelopmentCard();

    // Initiate a trade with another player, exchanging specified resources
    bool trade(Player* otherPlayer, Resource offer, Resource request, int offerCount, int requestCount);

    // Deduct resources from the player for building roads
    void deductResourcesForRoad();

    // Deduct resources from the player for building settlements
    void deductResourcesForSettlement();

    // Deduct resources from the player for building cities
    void deductResourcesForCity();

    // Deduct resources from the player for buying development cards
    void deductResourcesForDevelopmentCard();

    // Deduct a specified amount of a resource type from the player
    void deductResource(Resource type, int amount);

    // Print a list of buildings owned by the player
    void printBuildings() const;

    // Print the current resources owned by the player
    void printResources() const;

    // Static function to set the player with the biggest army (not implemented in this version)
    static void setBiggestArmy(Player* player);

    // Draw a random development card from a predefined list
    void drawDevelopmentCard();

    // Check if the player has won the game (assumed condition: 10 or more victory points)
    bool hasWon() const;

};

#endif // PLAYER_HPP
