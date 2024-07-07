/*
Shira Brosh
211821137
shira1d2631@gmail.com
*/

#include "Player.hpp"
#include "Building.hpp"
#include "Board.hpp"
#include "Settlement.hpp"
#include "Road.hpp"
#include "City.hpp"
#include "DevelopmentCard.hpp"
#include "KnightCard.hpp"
#include "VictoryPointCard.hpp"
#include "RoadBuildingCard.hpp"
#include "YearOfPlentyCard.hpp"
#include "MonopolyCard.hpp"
#include <algorithm> 
#include <iostream>
#include <cstdlib> 

// Constructor: Initializes a Player with a name and initializes resources to zero
Player::Player(std::string name) : name(name), victoryPoints(0), isTurn(false), roadsBuilt(0), countKnights(0) {
    // Initialize resources to zero
    resources[WOOD] = 0;
    resources[BRICK] = 0;
    resources[SHEEP] = 0;
    resources[WHEAT] = 0;
    resources[IRON] = 0;
}

// Destructor: Cleans up resources and memory allocated for development cards
Player::~Player() {
    // Free memory allocated for development cards
    for (DevelopmentCard* card : developmentCards) {
        delete card;
    }
    developmentCards.clear(); // Clear the vector of development cards
}

// Getter for the player's name
std::string Player::getName() const {
    return name;
}

// Getter for the player's turn status
const bool Player::getTurn() const {
    return isTurn;
}

// Getter for the player's count of knights
int Player::getCountKnights() {
    return countKnights;
}

// Getter for the player's victory points
int Player::getVictoryPoints() const {
    return victoryPoints;
}

// Getter for the player's list of buildings
std::vector<Building*> Player::getBuildings() const {
    return buildings;
}

// Non-const getter for the player's list of buildings (mutable version)
std::vector<Building*>& Player::getBuildings() {
    return buildings;
}

// Getter for the player's resources map
const std::unordered_map<Resource, int>& Player::getResources() const {
    return resources;
}

// Getter for the player's list of development cards (mutable version)
std::vector<DevelopmentCard*>& Player::getDevelopmentCards() {
    return developmentCards;
}

// Setter for the player's turn status
void Player::setTurn(bool turn) {
    isTurn = turn;
}

// Increment the count of knights owned by the player
void Player::addCountKnights() {
    countKnights++;
}

// Add a development card to the player's collection
void Player::addDevelopmentCard(DevelopmentCard* card) {
    developmentCards.push_back(card);
}

// Add to the player's victory points
void Player::addToVictoryPoints(int victory) {
    victoryPoints += victory;
}

// Remove from the player's victory points
void Player::removeVictoryPoints(int victory) {
    victoryPoints -= victory;
}

// Simulate rolling two dice and return their sum
int Player::rollDice() {
    int dice1 = rand() % 6 + 1; // Generate a random number between 1 and 6 for dice 1
    int dice2 = rand() % 6 + 1; // Generate a random number between 1 and 6 for dice 2
    int sum = dice1 + dice2; // Calculate the sum of the two dice rolls
    std::cout << "Roll Dice: " << sum << std::endl; // Output the result of the dice roll
    return sum;
}

// Add resources of a specific type and amount to the player
void Player::addResource(Resource r, int amount) {
    resources[r] += amount; // Increase the amount of the specified resource
}

// Count how many development cards of a specific type the player has
int Player::countDevelopmentCard(std::string nameCard) {
    int count = 0;
    for (int i = 0; i < developmentCards.size(); i++) {
        if (developmentCards[i]->getName() == nameCard) {
            count++;
        }
    }
    return count;
}

// Build a settlement at a specified vertex on the board
void Player::buildSettlement(int numVertex, Board& board) {
    std::cout << "Attempting to build settlement at vertex " << numVertex << " for player " << getName() << std::endl;

    // Check if the player has enough resources to build a settlement
    if (victoryPoints >= 2 &&
        (resources.at(WOOD) < 1 ||
         resources.at(BRICK) < 1 ||
         resources.at(WHEAT) < 1 ||
         resources.at(SHEEP) < 1)) {

        std::cout << "You don't have enough resources to build a settlement." << std::endl;
        return;
    }

    // Retrieve the vertex object from the board
    const Vertex& vertex = board.getVertexFromIndex(numVertex);

    // Check if the vertex already has a building (settlement or city)
    if (vertex.getBuilding() != nullptr) {
        std::cout << "Vertex already has a Settlement or City." << std::endl;
        return;
    }

    // Check if the vertex index is valid
    if (vertex.getNumIndex() == -1) {
        std::cout << "Vertex does not exist." << std::endl;
        return;
    }

    // Check adjacency rules for settlements
    if (vertex.hasAdjacentSettlement(board)) {
        std::cout << "Settlements need a space of two vertices between them." << std::endl;
        return;
    }

    bool isDeductResources = true;
    if (victoryPoints < 2) {
        isDeductResources = false;
    }

    // Create a new settlement object and attempt to build it on the board
    Settlement* settlement = new Settlement(this, numVertex);
    if (!settlement->buildSettlement(this, numVertex, board)) {
        delete settlement; // Clean up if settlement construction fails
        return;
    }

    buildings.push_back(settlement); // Add the settlement to the player's list of buildings
    addToVictoryPoints(1); // Increase player's victory points
    if (isDeductResources) {
        deductResourcesForSettlement(); // Deduct resources if conditions allow
    }
}

// Build a road between two specified vertices on the board
void Player::buildRoad(int numSource, int numTarget, Board& board) {
    std::cout << "Attempting to build road from vertex " << numSource << " to " << numTarget << " for player " << getName() << std::endl;

    // Check if the player has enough resources to build a road
    if (victoryPoints > 2 &&
        (resources.at(WOOD) < 1 ||
         resources.at(BRICK) < 1)) {

        std::cout << "You don't have enough resources to build a road." << std::endl;
        return;
    }

    // Validate vertex indices
    if (numSource < 0 || numSource >= board.getNumVertices() ||
        numTarget < 0 || numTarget >= board.getNumVertices()) {
        std::cout << "Invalid vertex indices for road building." << std::endl;
        return;
    }

    // Retrieve the path object from the board
    const Path& path = board.getPathFromIndexes(numSource, numTarget);

    // Check if the path exists on the board
    if (path.getSource() == -1 && path.getTarget() == -1) {
        std::cout << "Path not found between " << numSource << " and " << numTarget << "." << std::endl;
        return;
    }

    // Check if the path already has a building (road)
    if (path.getBuilding() != nullptr || path.hasRoad()) {
        std::cout << "Path is invalid or already has a building." << std::endl;
        return;
    }

    // Create a new road object and attempt to build it on the board
    Road* road = new Road(this, numSource, numTarget);
    if (!road->buildRoad(this, numSource, numTarget, board)) {
        delete road; // Clean up if road construction fails
        return;
    }

    buildings.push_back(road); // Add the road to the player's list of buildings
    roadsBuilt++; // Increase the road count

    // Deduct resources for roads if more than two roads are built
    if (roadsBuilt > 2) {
        deductResourcesForRoad();
    }
}

// Upgrade a settlement to a city at a specified vertex on the board
void Player::buildCity(int vertexIndex, Board& board) {
    std::cout << "Attempting to build city at vertex " << vertexIndex << " for player " << getName() << std::endl;

    // Retrieve the vertex object from the board
    const Vertex& vertex = board.getVertexFromIndex(vertexIndex);

    // Check if a settlement exists at the vertex
    if (vertex.getBuilding() == nullptr || vertex.getBuilding()->getType() != SETTLEMENT) {
        std::cout << "No settlement exists at this vertex to upgrade." << std::endl;
        return;
    }

    // Check if the player has enough resources to build a city
    if (resources.at(IRON) < 3 || resources.at(WHEAT) < 2) {
        std::cout << "You don't have enough resources to build a city." << std::endl;
        return;
    }

    // Create a new city object and attempt to upgrade the settlement on the board
    City* city = new City(this, vertexIndex);
    if (!city->upgradeToCity(this, vertexIndex, board)) {
        delete city; // Clean up if city construction fails
        return;
    }

    deductResourcesForCity(); // Deduct resources for building a city
    buildings.push_back(city); // Add the city to the player's list of buildings
    addToVictoryPoints(1); // Increase player's victory points
}

// Buy a development card if the player has enough resources
void Player::buildDevelopmentCard() {
    if (resources.at(SHEEP) < 1 || resources.at(IRON) < 1 || resources.at(WHEAT) < 1) {
        std::cout << "You don't have enough resources to buy a Development Card." << std::endl;
        return;
    }
    drawDevelopmentCard(); // Draw a random development card
}

// Initiate a trade with another player, exchanging specified resources
bool Player::trade(Player* otherPlayer, Resource offer, Resource request, int offerCount, int requestCount) {
    // Check if this player has enough resources to offer
    if (!hasEnoughResources(offer, offerCount)) {
        std::cout << "Player does not have enough " << Tile::resourceToString(offer) << " to offer." << std::endl;
        return false;
    }

    // Check if the other player has the requested resource
    if (!otherPlayer->hasEnoughResources(request, requestCount)) {
        std::cout << "Other player does not have the " << Tile::resourceToString(request) << " resource." << std::endl;
        return false;
    }

    // Deduct resources from this player and add to the other player
    deductResource(offer, offerCount);
    otherPlayer->addResource(offer, offerCount);

    // Deduct resources from the other player and add to this player
    otherPlayer->deductResource(request, requestCount);
    addResource(request, requestCount);

    std::cout << "Trade successful: exchanged " << offerCount << " " << Tile::resourceToString(offer) << " for " << requestCount << " " << Tile::resourceToString(request) << std::endl;
    return true;
}

// Deduct resources for building roads
void Player::deductResourcesForRoad() {
    resources[WOOD]--;
    resources[BRICK]--;
}

// Deduct resources for building settlements
void Player::deductResourcesForSettlement() {
    resources[WOOD]--;
    resources[BRICK]--;
    resources[SHEEP]--;
    resources[WHEAT]--;
}

// Deduct resources for building cities
void Player::deductResourcesForCity() {
    resources[IRON] -= 3;
    resources[WHEAT] -= 2;
}

// Deduct resources for buying development cards
void Player::deductResourcesForDevelopmentCard() {
    resources[IRON]--;
    resources[WHEAT]--;
    resources[SHEEP]--;
}

// Deduct a specific amount of a resource type from the player
void Player::deductResource(Resource type, int amount) {
    resources[type] -= amount;
    if (resources[type] < 0) {
        resources[type] = 0; // Ensure resources cannot go negative
    }
}

// Print a list of buildings owned by the player
void Player::printBuildings() const {
    std::cout << "Buildings for player " << name << ": ";
    for (const auto& building : buildings) {
        std::cout << "Vertex " << building->getVertex() << " has " << building->getBuildingTypeName() << ", ";
    }
    std::cout << std::endl;
}

// Print the current resources owned by the player
void Player::printResources() const {
    std::cout << getName() << "'s resources:" << std::endl;
    const std::unordered_map<Resource, int>& resources = getResources();
    for (const auto& [resource, amount] : resources) {
        std::cout << "  " << Tile::resourceToString(resource) << ": " << amount << std::endl;
    }
}

// Draw a random development card from a predefined list
void Player::drawDevelopmentCard() {
    static const std::vector<std::string> cardTypes = {"Knight", "victory_point", "road_building", "year_of_plenty", "monopoly"};
    std::string cardType = cardTypes[rand() % cardTypes.size()]; // Randomly select a card type
    DevelopmentCard* card = nullptr;

    // Create a development card object based on the selected type
    if (cardType == "Knight") {
        card = new KnightCard();
    } else if (cardType == "victory_point") {
        card = new VictoryPointCard();
    } else if (cardType == "road_building") {
        card = new RoadBuildingCard();
    } else if (cardType == "year_of_plenty") {
        card = new YearOfPlentyCard();
    } else if (cardType == "monopoly") {
        card = new MonopolyCard();
    }

    // Add the development card to the player's collection if valid
    if (card) {
        addDevelopmentCard(card);
    }
}

// Check if the player has enough of a specific resource type
bool Player::hasEnoughResources(Resource type, int amount) const {
    return resources.at(type) >= amount;
}

// Check if the player has won the game (assumed condition: 10 or more victory points)
bool Player::hasWon() const {
    return victoryPoints >= 10;
}
